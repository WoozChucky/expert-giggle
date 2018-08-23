/*
* export-giggle
* ScopedUnlock.hpp
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

#ifndef EXPORT_GIGGLE_SCOPEDUNLOCK_HPP
#define EXPORT_GIGGLE_SCOPEDUNLOCK_HPP

namespace  giggle::common::threading
{
	/**
	 * A class that simplifies thread synchronization
	 * with a mutex.
	 * The constructor accepts a Mutex and unlocks it.
	 * The destructor locks the mutex.
	 */
	template <class M>
	class ScopedUnlock
	{
	public:
		inline explicit ScopedUnlock(M& l_mutex, bool l_unlockNow = true): _mutex(l_mutex)
		{
			if (l_unlockNow)
				_mutex.Unlock();
		}
		inline ~ScopedUnlock()
		{
			try
			{
				_mutex.Lock();
			}
			catch (...)
			{
				// TODO: Throw unexpected error.
			}
		}

		ScopedUnlock() = delete;
		ScopedUnlock(const ScopedUnlock&) = delete;
		ScopedUnlock& operator = (const ScopedUnlock&) = delete;

	private:
		M& _mutex;


	};
}


#endif //EXPORT_GIGGLE_SCOPEDUNLOCK_HPP
