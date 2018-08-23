/*
* export-giggle
* MutexImpl.hpp
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

#ifndef EXPORT_GIGGLE_MUTEXIMPL_HPP
#define EXPORT_GIGGLE_MUTEXIMPL_HPP

#include <pthread.h>
#include <errno.h>

#include <exceptions/Exception.hpp>
#include <Types.hpp>

using namespace giggle::common::exception;

namespace giggle::common::threading
{
	class MutexImpl
	{
	public:
		enum MutexTypeImpl
		{
			MUTEX_RECURSIVE_IMPL,
			MUTEX_NONRECURSIVE_IMPL
		};
	protected:

		explicit MutexImpl(MutexTypeImpl l_type);

		~MutexImpl();

		inline void LockImpl()
		{
			if (pthread_mutex_lock(&_mutex))
				throw Exception("Cannot lock mutex.");
		}

		inline bool TryLockImpl()
		{
			int rc = pthread_mutex_trylock(&_mutex);
			if (rc == 0)
				return true;
			else if (rc == EBUSY)
				return false;
			else
				throw Exception("Cannot lock mutex");
		}

		bool TryLockImpl(UInt64 l_milliseconds);

		inline void UnlockImpl()
		{
			if (pthread_mutex_unlock(&_mutex))
				throw Exception("Cannot unlock mutex.");
		}

	private:
		pthread_mutex_t _mutex;

	};

	class FastMutexImpl : public MutexImpl
	{
	protected:
		FastMutexImpl();
		~FastMutexImpl() = default;
	};


}




#endif //EXPORT_GIGGLE_MUTEXIMPL_HPP
