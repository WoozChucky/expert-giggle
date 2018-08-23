/*
* export-giggle
* SingletonHolder.hpp
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

#ifndef EXPORT_GIGGLE_SINGLETONHOLDER_HPP
#define EXPORT_GIGGLE_SINGLETONHOLDER_HPP

#include <threading/Mutex.hpp>

namespace giggle::common
{
	/**
	 * This is a helper template class for managing
	 * singleton objects allocated on the heap.
	 * The class ensures proper deletion (including
	 * calling of the destructor) of the singleton objects
	 * when the application that created them terminates.
	 */
	 template <class S>
	class SingletonHolder
	{
	public:
		SingletonHolder():
			_ptr(0)
		{

		}

		~SingletonHolder()
		{
			delete _ptr;
		}

		/**
		 * Returns a pointer to the singleton object
		 * hold by the SingletonHolder. The first call
		 * to get will create the singleton.
		 */
		S* Get()
		{
			threading::FastMutex::ScopedLock lock(_mutex);

			if (!_ptr)
				_ptr = new S;
			return _ptr;
		}

		/**
		 * Deletes the singleton object
		 */
		void Reset()
		{
			delete _ptr;
			_ptr = 0;
		}

	private:
		S* _ptr;
		threading::FastMutex _mutex;

	};

} // namespace common

#endif //EXPORT_GIGGLE_SINGLETONHOLDER_HPP
