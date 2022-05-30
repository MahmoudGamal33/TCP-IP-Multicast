// // Our Reciever (Client)

#include <iostream>
#include <thread>
#include <chrono>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define SOCKET_SUCCESS (0)
#define MAX_STRING_LENGTH (30)

double calculateAverage(int64_t accumulative, int64_t counter)
{
    return accumulative / (double)counter;
}

void display(int64_t accumulative, int64_t counter)
{
    std::cout << "**************************\n";
    std::cout << "Accumulative Degrees: " << accumulative << std::endl;
    std::cout << "Average Degrees: " << calculateAverage(accumulative, counter) << std::endl;
    std::cout << "**************************\n";
}

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

    char recvString[MAX_STRING_LENGTH + 1] = {0}; // Buffer to receive into
    
    // Receive a single datagram from the server

    int64_t connectionCounter = 0;
    int64_t accumulativeDegrees = 0;

    while(true)
    {
        int recvStringLen = recvfrom(sock, recvString, MAX_STRING_LENGTH, 0, NULL, 0);
        if (recvStringLen < 0)
        {
            std::cerr << "ERROR: recvfrom() failed.\n";
            exit(EXIT_FAILURE);
        }

        recvString[recvStringLen] = '\0'; // Terminate the received string

        accumulativeDegrees += atoi(recvString);
 
        if(++connectionCounter % 5 == 0)
        {
            display(accumulativeDegrees, connectionCounter);
        }
    }

    close(sock);

    return 0;
}