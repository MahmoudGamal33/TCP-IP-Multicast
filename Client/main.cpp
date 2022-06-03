// // Our Reciever (Client)

#include <Helpers/Inc/calculation_helper.hpp>


#define SOCKET_SUCCESS (0)

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage Minimum: clientAPP <multicast_address> <Port> \n";
            exit(EXIT_FAILURE);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    }

    char *multicastAddrString = argv[1]; // First arg: multicast addr v4
    char *portService = argv[2];         // Second arg: port/service

    struct addrinfo addrCriteria = {0}; // Criteria for address match

    addrCriteria.ai_family = PF_INET;        // v4 OK
    addrCriteria.ai_socktype = SOCK_DGRAM;   // Only datagram sockets
    addrCriteria.ai_protocol = IPPROTO_UDP;  // Only UDP protocol
    addrCriteria.ai_flags |= AI_NUMERICHOST; // Don't try to resolve address

    // Get address information
    struct addrinfo *multicastAddr = NULL; // List of server addresses
    int retunedStatus = getaddrinfo(multicastAddrString, portService, &addrCriteria, &multicastAddr);
    if (SOCKET_SUCCESS != retunedStatus)
    {
        std::cerr << "ERROR: getaddrinfo() failed " << gai_strerror(retunedStatus) << "\n";
        exit(EXIT_FAILURE);
    }

    // Create socket to receive on
    int sock = socket(multicastAddr->ai_family, multicastAddr->ai_socktype, multicastAddr->ai_protocol);

    if (-1 == sock)
    {
        std::cerr << "ERROR: socket() failed.\n";
        exit(EXIT_FAILURE);
    }

    int optval = 1;
    retunedStatus = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&optval, sizeof(optval));
    if (SOCKET_SUCCESS != retunedStatus)
    {
        std::cerr << "ERROR: setsockopt(IPV4_ADD_MEMBERSHIP) failed.\n";
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in bindingAddr = {0};
    bindingAddr.sin_family = multicastAddr->ai_family;
    bindingAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindingAddr.sin_port = ((struct sockaddr_in *)multicastAddr->ai_addr)->sin_port; // htons((uint16_t)(atoi(portService)));

    retunedStatus = bind(sock, (struct sockaddr *)&bindingAddr, sizeof(bindingAddr));
    if (-1 == retunedStatus)
    {
        std::cerr << "ERROR: bind() failed.\n";
        exit(EXIT_FAILURE);
    }

    if (multicastAddr->ai_family == AF_INET)
    {
        // Now join the multicast "group"
        struct ip_mreq joinRequest = {0};
        joinRequest.imr_multiaddr = ((struct sockaddr_in *)multicastAddr->ai_addr)->sin_addr;
        joinRequest.imr_interface.s_addr = htonl(INADDR_ANY); // Let the system choose the i/f

        std::cout << "Joining IPv4 multicast group...\n";

        retunedStatus = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &joinRequest, sizeof(joinRequest));

        if (SOCKET_SUCCESS != retunedStatus)
        {
            std::cerr << "ERROR: setsockopt(IPV4_ADD_MEMBERSHIP) failed.\n";
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "ERROR: Unknown address family.\n";
        exit(EXIT_FAILURE);
    }

    // Free address structure(s) allocated by getaddrinfo()
    freeaddrinfo(multicastAddr);

    // char recvString[MAX_STRING_LENGTH + 1] = {0}; // Buffer to receive into
    
    // Receive a single datagram from the server

    std::thread recvThread(&recvFromServer, sock);
    std::thread displayThread(&display);

    recvThread.join();
    displayThread.join();

    close(sock);

    return 0;
}