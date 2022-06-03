// Our Sender (Node)

#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define SOCKET_SUCCESS  (0)

#define MAX_STRING_LENGTH (30)

int main(int argc, char *argv[])
{
    try {
        if (argc < 3 || argc > 4)
        {
            std::cerr << "Usage: serverApp <multicast_address> <Port> <Send String> [<TTL>]\n";
            exit(EXIT_FAILURE);
        }
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    }

    char *multicastIPString = argv[1]; // First arg: multicast IP address
    char *portService = argv[2]; // Second arg: multicast port/service

    // Fourth arg (optional): TTL for transmitting multicast packets (IP_MULTICAST_TTL unsigned char 0 - 255 Time-to-live for multicast IP packets)
    int validTTL = (argc == 4) ? atoi(argv[3]) : 1;
    unsigned char multicastTTL =  (validTTL > 0 && validTTL <= 255) ? (unsigned char)validTTL : 1;

    // Tell the system what kind(s) of address info we want
    struct addrinfo nodeAddressCriteria = {0};
    nodeAddressCriteria.ai_family = PF_INET; // v4 OK
    nodeAddressCriteria.ai_socktype = SOCK_DGRAM; // Only datagram sockets
    nodeAddressCriteria.ai_protocol = IPPROTO_UDP; // Only UDP
    nodeAddressCriteria.ai_flags |= AI_NUMERICHOST; // Don't try to resolve address

    struct addrinfo *multicastAddressInfo = NULL; // Holder for returned address
    int retunedStatus = getaddrinfo(multicastIPString, portService, &nodeAddressCriteria, &multicastAddressInfo);

    if(SOCKET_SUCCESS != retunedStatus)
    {
        std::cerr << "ERROR: getaddrinfo() failed " << gai_strerror(retunedStatus) << "\n";
        exit(EXIT_FAILURE);
    }

    // Create socket for sending datagrams
    int sock = socket(multicastAddressInfo->ai_family, multicastAddressInfo->ai_socktype, multicastAddressInfo->ai_protocol);

    if(-1 == sock)
    {
        std::cerr << "ERROR: socket() failed.\n";
        exit(EXIT_FAILURE);
    }

    if(multicastAddressInfo->ai_family == AF_INET)
    {
        retunedStatus = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, &multicastTTL, sizeof(multicastTTL));
        if(SOCKET_SUCCESS != retunedStatus)
        {
            std::cerr << "ERROR: setsockopt() failed.\n";
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        std::cerr << "ERROR: Unable to set TTL (invalid address family).\n";
        exit(EXIT_FAILURE);
    }
    // int64_t acc = 0;
    // int64_t c = 0;
    while(true)
    {
        // Multicast the string to all who have joined the group
        char sendString[MAX_STRING_LENGTH] = {0};
        size_t sendStringLen = 0;

        int degreeC = rand() % 35;

        sprintf(sendString, "%d", degreeC);
        sendStringLen = strlen(sendString);
        // acc += degreeC;
        // c++;

        // std::cout << "*********************** " << std::endl;
        // std::cout << "Accumulative Degrees: " << acc << std::endl;
        // std::cout << "Average Degrees: " <<  acc / (double)c << std::endl;

        ssize_t numBytes = sendto(sock, sendString, sendStringLen, 0, multicastAddressInfo->ai_addr, multicastAddressInfo->ai_addrlen);
        if(-1 == numBytes)
        {
            std::cerr << "ERROR: sendto() failed.\n";
            exit(EXIT_FAILURE);
        }
        else if(numBytes != sendStringLen)
        {
            std::cerr << "ERROR: sendto() wrong number of bytes.\n";
            exit(EXIT_FAILURE);
        }
        else
        {
            //do nothing
        }

        sleep(1);
    }

    return 0;
}
