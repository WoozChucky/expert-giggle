/*
* export-giggle
* Mutex.hpp
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

#ifndef EXPORT_GIGGLE_MUTEX_HPP
#define EXPORT_GIGGLE_MUTEX_HPP

#include "ScopedLock.hpp"
#include "MutexImpl.hpp"

namespace giggle::common::threading
{

	/**
	* A FastMutex (mutual exclusion) is similar to a Mutex.
	* Locking a FastMutex is guaranteed to be at least as
	* fast as locking a Mutex.  However, a FastMutex is not
	* guaranteed to be either recursive or non-recursive.
	* It is best suited to thread safe components like pools,
	* caches and queues where locking is internal to the component.
	* Using the ScopedLock class is the preferred way to automatically
	* lock and unlock a mutex.
	*/
	class FastMutex : private FastMutexImpl
	{
	public:
		typedef ScopedLock<FastMutex> ScopedLock;

		/**
		 * Creates the Mutex.
		 */
		FastMutex() = default;

		/**
		 * Destroys the Mutex.
		 */
		~FastMutex() = default;

		FastMutex(const FastMutex&) = delete;
		FastMutex& operator = (const FastMutex&) = delete;

		/**
		 * Locks the mutex. Blocks if the mutex
		 * is held by another thread.
		 */
		inline void Lock()
		{
			LockImpl();
		}

		/**
		 * Locks the mutex. Blocks up to the given number of milliseconds
		 * if the mutex is held by another thread. Throws a TimeoutException
		 * if the mutex ca not be held within the given timeout.
		 *
		 * @param l_milliseconds
		 */
		inline void Lock(UInt64 l_milliseconds)
		{
			if (TryLockImpl(l_milliseconds))
				throw Exception("Timeout occurred.");
		}

		/**
		 * Locks the mutex. Blocks up to the given number of milliseconds
		 * if the mutex is held by another thread.
		 *
		 * @return true if the mutex was successfully locked.
		 */
		inline bool TryLock()
		{
			return TryLockImpl();
		}

		/**
		 * Locks the mutex. Blocks up to the given number of milliseconds
		 * if the mutex is held by another thread.
		 *
		 * @param l_milliseconds
		 * @return true if the mutex was successfully locked.
		 */
		inline bool TryLock(UInt64 l_milliseconds)
		{
			return TryLockImpl(l_milliseconds);
		}

		/**
		 * Unlocks the mutex so that it can be acquired by
		 * other threads.
		 */
		inline void Unlock()
		{
			UnlockImpl();
		}

	};

}

#endif //EXPORT_GIGGLE_MUTEX_HPP
