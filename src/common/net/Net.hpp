/*
* export-giggle
* Net.hpp
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

#ifndef EXPORT_GIGGLE_NET_HPP
#define EXPORT_GIGGLE_NET_HPP

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <Types.hpp>

namespace giggle::common::net
{

	typedef struct sockaddr_in SocketAddress;
	typedef int SocketFileDescriptor;

	const UInt32 DEFAULT_MAX_CONNECTIONS = 128;

} // namespace net

#endif //EXPORT_GIGGLE_NET_HPP
