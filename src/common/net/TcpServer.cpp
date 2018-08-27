/*
* export-giggle
* TcpServer.cpp
* Created by Nuno Levezinho on 24/08/2018.
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

#include "TcpServer.hpp"

#include <exceptions/SystemException.hpp>
#include <memory/MemoryPool.hpp>
#include <iostream>
#include <arpa/inet.h>

using namespace giggle::common::net;
using namespace giggle::common::exception;
using namespace giggle::common::threading;
using namespace giggle::common::memory;

TcpServer::TcpServer(UInt32 l_port, UInt32 l_maxConnections):
	_clientAddress{}, _serverAddress{},
	_port(l_port), _running(false),
	_maxConnections(l_maxConnections),
	_connectedClients(0),
	_clients(),
	_threadPool(new threading::ThreadPool(_maxConnections / 2)),
	_memoryPool(new memory::MemoryPool(DEFAULT_BLOCK_SIZE, 10, DEFAULT_MAX_BLOCKS))
{

}

TcpServer::~TcpServer()
{
	if (_running)
	{
		_running = false;
		Close();
	}

	delete _threadPool;
}

void TcpServer::Close()
{
	if(_running)
	{
		_running = false;
		for(auto client : _clients)
		{
			std::cout << "Removing client " << client << "." << std::endl;
			close(client);
		}
		std::cout << "Closing server descriptor" << std::endl;
		close(_serverDescriptor);
	}
}

void TcpServer::Listen()
{
	_serverDescriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverDescriptor < 0)
	{
		std::cerr << errno << std::endl;

		throw exception::SystemException("Error opening socket.");
	}

	bzero((char *) &_serverAddress, sizeof(_serverAddress));

	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_port);

	if (bind(_serverDescriptor, (struct sockaddr *) &_serverAddress, sizeof(_serverAddress)) < 0)
	{
		std::cerr << errno << std::endl;

		close(_serverDescriptor);
		throw exception::SystemException("Error binding socket.");
	}

	if (listen(_serverDescriptor, _maxConnections) != 0)
	{
		std::cerr << errno << std::endl;

		close(_serverDescriptor);
	}

	_running = true;

	auto clientLength = static_cast<unsigned int>(sizeof(_clientAddress));

	std::cout << "Ready to accept connections..." << std::endl;

	while (true)
	{

		_clientDescriptor = accept(_serverDescriptor, (struct sockaddr *) &_clientAddress, &clientLength);

		if (_clientDescriptor < 0)
		{
			// todo
			std::cerr << errno << std::endl;
		}
		else
		{
			_connectedClients++;

			if (_connectedClients > _maxConnections)
			{
				close(_clientDescriptor);
				_connectedClients--;
			}
			else
			{
				_clients.push_back(_clientDescriptor);

				auto connection = GetClient(_clientDescriptor);

				_threadPool->enqueue([](ClientConnection l_connection)
									 {
										TcpServer::HandleConnection(l_connection);
									 }, connection);
			}
		}

		if (!_running)
		{
			break;
		}
	}

}

TcpServer::ClientConnection TcpServer::GetClient(SocketFileDescriptor l_descriptor)
{
	struct sockaddr_in addr{};
	auto addr_size = static_cast<socklen_t>(sizeof(struct sockaddr_in));

	getpeername(l_descriptor, (struct sockaddr *)&addr, &addr_size);

	auto client_ip = new char[30];
	strcpy(client_ip, inet_ntoa(addr.sin_addr));

	ClientConnection connection {};
	connection.Authenticated 			= false;
	connection.Connected 				= true,
	connection.Descriptor 				= l_descriptor;
	connection.IPAddress 				= client_ip;
	connection.Port 					= ntohs(addr.sin_port);
	connection.Buffer 					= _memoryPool->GetMemory();

	return connection;
}

void * TcpServer::HandleConnection(ClientConnection l_connection)
{

	while (l_connection.Connected)
	{
		auto bytesRead = recv(l_connection.Descriptor, l_connection.Buffer, sizeof(l_connection.Buffer), 0);

		break;
	}

	// Returns the buffer so it can be properly freed from memory
	return l_connection.Buffer;
}


