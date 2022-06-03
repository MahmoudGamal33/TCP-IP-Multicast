#include <Helpers/Inc/calculation_helper.hpp>
#include <mutex>

uint64_t connectionCounter = 0;
uint64_t accumulativeDegrees = 0;

std::mutex mtx;

void recvFromServer(int __fd)
{
    while(true)
    {
        char recvString[MAX_STRING_LENGTH + 1] = {0};
        int recvStringLen = recvfrom(__fd, (void*)recvString, MAX_STRING_LENGTH, 0, NULL, 0);
        if (recvStringLen < 0)
        {
            std::cerr << "ERROR: recvfrom() failed.\n";
            exit(EXIT_FAILURE);
        }

        recvString[recvStringLen] = '\0'; // Terminate the received string

        mtx.lock();
        accumulativeDegrees += atoi(recvString);
        connectionCounter += 1;
        mtx.unlock();
    }
}


void display(void)
{
    while(true)
    {
        std::cout << "**************************\n";
        mtx.lock();
        std::cout << "Accumulative Degrees: " << accumulativeDegrees << std::endl;
        std::cout << "Average Degrees: " << (connectionCounter > 0 ? (accumulativeDegrees / (double)connectionCounter) : 0.0) << std::endl;
        mtx.unlock();
        std::cout << "**************************\n";

        std::this_thread::sleep_for (std::chrono::seconds(5));
    }
}