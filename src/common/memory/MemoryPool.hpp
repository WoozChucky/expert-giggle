/*
* export-giggle
* MemoryPool.hpp
* Created by Nuno Levezinho on 09/08/2018.
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

#ifndef EXPORT_GIGGLE_MEMORYPOOL_HPP
#define EXPORT_GIGGLE_MEMORYPOOL_HPP

#include <cstdio>
#include <vector>
#include <mutex>

namespace giggle::common::memory
{
	/**
	 * @brief A simple pool for fixed-size memory blocks.
	 *
	 * The main purpose of this class is to speed-up
	 * memory allocations, as well as to reduce memory
	 * fragmentation in situations where same blocks
	 * are allocated all over again, such as in server
	 * applications.
	 *
	 * All allocated blocks are retained for future use.
	 * A limit on the number of blocks can be specified.
	 * Blocks can be preallocated.
	 */
	class MemoryPool {

	public:

		/**
		 * @brief Creates a MemoryPool for blocks with given l_block_size.
		 * The number of blocks given in l_pre_alloc are preallocated.
		 * @param l_block_size The size of a block.
		 * @param l_pre_alloc  The number of blocks to preallocate.
		 * @param l_max_alloc  The max number of blocks that can be preallocated.
		 */
		explicit MemoryPool(std::size_t l_block_size, int l_pre_alloc = 0, int l_max_alloc = 0);

		~MemoryPool();

		/**
		 * @brief Returns a memory block.
		 * If there are no more blocks in the pool, a new block will be allocated.
		 *
		 * If maxAlloc blocks are already allocated, an
		 * OutOfMemory exception is thrown.
		 *
		 */
		void* GetMemory();

		/**
		 * @brief Releases a memory block and returns it to the pool
		 * @param l_ptr The memory block
		 */
		void Release(void* l_ptr);

		/**
		 * @brief Returns the size of a block.
		 *
		 */
		std::size_t BlockSize() const;

		/**
		 * @brief Returns the number of allocated blocks.
		 *
		 */
		int Allocated() const;

		/**
		 * @brief Returns the number of available blocks in the pool.
		 *
		 */
		int Available() const;

	private:

		MemoryPool();
		MemoryPool(const MemoryPool&);
		MemoryPool& operator= (const MemoryPool&);

		void Clear();

		enum
		{
			BLOCK_RESERVE = 128
		};

		typedef std::vector<char*> BlockVec;

		std::size_t _block_size;
		int 		_max_alloc;
		int 		_allocated;
		BlockVec	_blocks;
		std::mutex	_mutex;

	};

} // namespace memory

#endif //EXPORT_GIGGLE_MEMORYPOOL_HPP
