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
#include <iostream>

using namespace giggle::common::net;
using namespace giggle::common::exception;
using namespace giggle::common::threading;

TcpServer::TcpServer(UInt32 l_port, UInt32 l_maxConnections):
	_clientAddress{}, _serverAddress{},
	_port(l_port), _running(false),
	_maxConnections(l_maxConnections),
	_connectedClients(0),
	_clients(),
	_threadPool(new threading::ThreadPool(_maxConnections / 2))
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
			std::cout << "Removing client" << std::endl;
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
		throw exception::SystemException("Error opening socket.");
	}

	bzero((char *) &_serverAddress, sizeof(_serverAddress));

	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_port);

	if (bind(_serverDescriptor, (struct sockaddr *) &_serverAddress, sizeof(_serverAddress)) < 0)
	{
		close(_serverDescriptor);
		throw exception::SystemException("Error binding socket.");
	}

	if (listen(_serverDescriptor, _maxConnections) != 0)
	{
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

				_threadPool->enqueue([](SocketFileDescriptor l_descriptor)
									 {
										TcpServer::HandleConnection(l_descriptor);
									 }, _clientDescriptor);
			}
		}

		if (!_running)
		{
			break;
		}
	}

}

void * TcpServer::HandleConnection(SocketFileDescriptor l_descriptor)
{

	return nullptr;
}
