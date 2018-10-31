/*
* export-giggle
* app.cpp
* Created by Nuno Levezinho on 01/07/2018.
*
* Copyright (c) 2018 [Nuno Levezinho] All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*/

#include <cstdlib>
#include <iostream>
#include <signal.h>

#include <net/TcpServer.hpp>

using namespace giggle::common::net;

TcpServer* server = nullptr;

void my_handler(int l_action)
{
	std::cout << "Caught action -> " << l_action << std::endl;
	server->Close();
}



int main(int argc, char** argv)
{
	struct sigaction signHandler{};

	signHandler.sa_handler = my_handler;
	sigemptyset(&signHandler.sa_mask);
	signHandler.sa_flags = 0;

	sigaction(SIGINT, &signHandler, nullptr);
	sigaction(SIGQUIT, &signHandler, nullptr);
	sigaction(SIGTERM, &signHandler, nullptr);

	// Used usually on another process
	// kill(::getpid(), SIGTERM);
	// Used usually on the same(self) process
	// raise(SIGTERM);

	auto pool = new giggle::common::memory::MemoryPool(256, 0, 100);

	auto block = static_cast<char *>(pool->GetMemory());

	if (block)
	{
		std::cout << "Block allocated -> " << sizeof(block) << std::endl;
	}

    //server = new TcpServer(8050, 128);
    //server->Listen();

    std::cout << "Application" << std::endl;
    return EXIT_SUCCESS;
}
