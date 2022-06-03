#ifndef _HELPERS_
#define _HELPERS_

#include <iostream>
#include <thread>
#include <chrono>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAX_STRING_LENGTH (30)

void recvFromServer(int __fd);

void display(void);

#endif