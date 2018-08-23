/*
* export-giggle
* ScopedLock.hpp
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

#ifndef EXPORT_GIGGLE_SCOPEDLOCK_HPP
#define EXPORT_GIGGLE_SCOPEDLOCK_HPP

#include <Types.hpp>

namespace giggle::common::threading
{
	/**
	 * A class that simplifies thread synchronization
	 * with a mutex.
	 * The constructor accepts a Mutex (and optionally
	 * a timeout value in milliseconds) and locks it.
	 *
	 * The destructor unlocks the mutex.
	 */
	 template <class M>
	class ScopedLock
	{
	public:
		explicit ScopedLock(M& l_mtx):
			_mutex(l_mtx)
		{
			_mutex.Lock();
		}

		explicit ScopedLock(M& l_mtx, Int64 miliseconds):
				_mutex(l_mtx)
		{
			_mutex.Lock(miliseconds);
		}

		~ScopedLock()
		{
			try
			{
				_mutex.Unlock();
			}
			catch (...)
			{
				// TODO: Throw unexpected error.
			}

		}

		ScopedLock() = delete;
		ScopedLock(const ScopedLock&) = delete;
		ScopedLock& operator = (const ScopedLock&) = delete;

	private:
		M& _mutex;

	};

	/**
	* A class that simplifies thread synchronization
	* with a mutex.
	* The constructor accepts a Mutex (and optionally
	* a timeout value in milliseconds) and locks it.
	*
	* The destructor unlocks the mutex.
	*
	* The Unlock() member function allows for manual
	* unlocking of the mutex.
	*/
	template <class M>
	class ScopedLockWithUnlock
	{
	public:
		explicit ScopedLockWithUnlock(M& l_mtx):
				_ptrMutex(l_mtx)
		{
			_ptrMutex->Lock();
		}

		explicit ScopedLockWithUnlock(M& l_mtx, Int64 miliseconds):
				_ptrMutex(l_mtx)
		{
			_ptrMutex->Lock(miliseconds);
		}

		~ScopedLockWithUnlock()
		{
			try
			{
				Unlock();
			}
			catch (...)
			{
				// TODO: Throw unexpected error.
			}

		}

		ScopedLockWithUnlock() = delete;
		ScopedLockWithUnlock(const ScopedLockWithUnlock&) = delete;
		ScopedLockWithUnlock& operator = (const ScopedLockWithUnlock&) = delete;

		void Unlock()
		{
			if (_ptrMutex)
			{
				_ptrMutex->Unlock();
				_ptrMutex = 0;
			}
		}

	private:
		M* _ptrMutex;

	};

} // namespace threading




#endif //EXPORT_GIGGLE_SCOPEDLOCK_HPP
