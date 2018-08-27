/*
* export-giggle
* TcpServer.hpp
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

#ifndef EXPORT_GIGGLE_TCPSERVER_HPP
#define EXPORT_GIGGLE_TCPSERVER_HPP

#include "Net.hpp"

#include <threading/ThreadPool.hpp>
#include <memory/MemoryPool.hpp>

namespace giggle::common::net
{

	class TcpServer
	{
	public:
		explicit TcpServer(UInt32 l_port, UInt32 l_maxConnections = DEFAULT_MAX_CONNECTIONS);
		~TcpServer();

		TcpServer(const TcpServer& l_other) = delete;
		TcpServer & operator = (const TcpServer&) = delete;

		void Listen();
		void Close();

	private:

		typedef struct {
			SocketFileDescriptor Descriptor;
			std::string IPAddress;
			UInt16 Port;
			bool Connected;
			bool Authenticated;
			void* Buffer;
		} ClientConnection;

		static void * HandleConnection(ClientConnection l_connection);

		ClientConnection GetClient(SocketFileDescriptor l_descriptor);

		const UInt32 _port;
		const UInt32 _maxConnections;

		UInt32 _connectedClients;

		std::vector<SocketFileDescriptor> _clients;

		SocketAddress _serverAddress;
		SocketAddress _clientAddress;

		SocketFileDescriptor _serverDescriptor;
		SocketFileDescriptor _clientDescriptor;

		threading::ThreadPool* _threadPool;
		// threading::FastMutex _mutex;
		memory::MemoryPool* _memoryPool;

		bool _running;
	};

} // namespace net


#endif //EXPORT_GIGGLE_TCPSERVER_HPP
