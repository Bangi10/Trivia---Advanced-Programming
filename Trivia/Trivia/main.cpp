#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include <thread>
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "Starting... " << std::endl;
	WSAInitializer wsa_init;  // at the end of this block the WSA will be closed 
	Server mt_server;
	mt_server.run();
}