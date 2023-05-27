#pragma comment (lib, "ws2_32.lib")
#include "Server.h"
#include "SqliteDatabase.h"
<<<<<<< HEAD
#include <thread>
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
=======
#include "WSAInitializer.h"
#include <iostream>
>>>>>>> b868f45fac1eaef5f37d1b0e9f2bb14fca8e6a21
#include <memory>

int main()
{
	std::cout << "Starting... " << std::endl;
	WSAInitializer wsa_init;  // at the end of this block the WSA will be closed 
	std::shared_ptr<IDatabase> db = std::make_shared<SqliteDatabase>();
	Server mt_server(db);
	mt_server.run();
}