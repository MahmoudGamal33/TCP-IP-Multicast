# TCP-IP-Multicast
One Sender -> Multiple Recipients

![Untitled](https://user-images.githubusercontent.com/60486460/171030937-33a494d9-842d-4a95-a425-46a205e9ec3b.jpg)


## Overview

Let's Go Beyond Basic Socket Programming. 
This TCP/IP Multicasting Example demonstrates advanced principles for socket programming.

For the sender; using multicast is very similar to using unicast. The difference is in the form
of the address. A multicast address identifies a set of receivers who have “asked” the network
to deliver messages sent to that address.
A range of the address space is set aside for multicast in both IPv4 and IPv6. IPv4 multicast
addresses are in the range 224.0.0.0 to 239.255.255.255.


## Build and Test

./build/serverAPP 239.255.0.1 3001 
./build/clientAPP 239.255.0.1 3001 
