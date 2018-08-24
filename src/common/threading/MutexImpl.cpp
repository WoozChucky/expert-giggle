/*
* export-giggle
* MutexImpl.cpp
* Created by nunol on 8/23/2018.
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

#include "MutexImpl.hpp"

using namespace giggle::common::threading;

giggle::common::threading::MutexImpl::MutexImpl(giggle::common::threading::MutexImpl::MutexTypeImpl l_type)
{
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);

	pthread_mutexattr_settype(&attr, l_type == MUTEX_RECURSIVE_IMPL ? PTHREAD_MUTEX_RECURSIVE : PTHREAD_MUTEX_NORMAL);

	if (pthread_mutex_init(&_mutex, &attr))
	{
		pthread_mutexattr_destroy(&attr);
		throw Exception("Cannot create mutex");
	}
	pthread_mutexattr_destroy(&attr);
}

giggle::common::threading::MutexImpl::~MutexImpl()
{
	pthread_mutex_destroy(&_mutex);
}

bool giggle::common::threading::MutexImpl::TryLockImpl(giggle::common::UInt64 l_milliseconds)
{
	// TODO: Implement this
	return false;
}

// FastMutex

giggle::common::threading::FastMutexImpl::FastMutexImpl() :
	MutexImpl(MUTEX_NONRECURSIVE_IMPL)
{

}
