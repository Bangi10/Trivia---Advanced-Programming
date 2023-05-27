#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "SqliteDatabase.h"
#include "WSAInitializer.h"
#include <iostream>
#include <memory>

int main()
{
	std::cout << "Starting... " << std::endl;
	WSAInitializer wsa_init;  // at the end of this block the WSA will be closed 
	std::shared_ptr<IDatabase> db = std::make_shared<SqliteDatabase>();
	Server mt_server(db);
	mt_server.run();
}