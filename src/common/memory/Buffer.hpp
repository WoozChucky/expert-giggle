/*
* export-giggle
* Buffer.hpp
* Created by Nuno Levezinho on 22/08/2018.
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

#ifndef EXPORT_GIGGLE_BUFFER_HPP
#define EXPORT_GIGGLE_BUFFER_HPP

#include <cstddef>
#include <cstring>
#include <exceptions/InvalidAccessException.hpp>
#include <exceptions/IndexOutOfBoundsException.hpp>

namespace giggle::common::memory
{

	/**
	 * A buffer class that allocates a buffer og a given type and size
	 * in the constructor and deallocates the buffer in the destructor.
	 *
	 * This class is useful everywhere where a temporary buffer
	 * is needed.
	 */
	template <class T>
	class Buffer
	{
	public:

		/**
		 * @brief Creates and allocates the Buffer.
		 * @param l_length The buffer size.
		 */
		explicit Buffer(std::size_t l_length):
			_capacity(l_length),
			_used(l_length),
			_ptr(0),
			_ownMem(true)
		{
			if (l_length > 0)
			{
				_ptr = new T[l_length];
			}
		}

		/**
		 * Creates the Buffer. Length argument specifies the length
		 * of the supplied memory pointed to by l_pMem in the number
		 * of elements of type T. Supplied pointer is considered
		 * blank and not owned by Buffer, so in this case Buffer
		 * only acts as a wrapper around externally supplied
		 * (and lifetime-managed) memory.
		 */
		Buffer(T* l_pMem, std::size_t l_length):
			_capacity(l_length),
			_used(l_length),
			_ptr(l_pMem),
			_ownMem(false)
		{

		}

		/**
		 * Creates and allocates the Buffer; copies the contents of
		 * the supplied memory into the buffer. Length argument specifies
		 * the length of the supplied memory pointed to by pMem in the
		 * number of elements of type T.
		 */
		Buffer(const T* l_pMem, std::size_t l_length):
			_capacity(l_length),
			_used(l_length),
			_ptr(0),
			_ownMem(true)
		{
			if (_capacity > 0)
			{
				_ptr = new T[_capacity];
				std::memcpy(_ptr, _used * sizeof(T));
			}
		}

		/**
		 * @brief Copy constructor.
		 * @param l_other
		 */
		Buffer(const Buffer& l_other):
			_capacity(l_other._used),
			_used(l_other._used),
			_ptr(0),
			_ownMem(true)
		{
			if (_used)
			{
				_ptr = new T[_used];
				std::memcpy(_ptr, l_other._ptr, _used * sizeof(T));
			}
		}

		/**
		 * @brief Assignment operator.
		 * @param l_other
		 * @return
		 */
		Buffer& operator = (const Buffer& l_other)
		{
			if (this != &l_other)
			{
				Buffer tmp(l_other);
				Swap(tmp);
			}
			return *this;
		}

		/**
		 * @brief Copy constructor.
		 * @param l_other
		 */
		Buffer(Buffer&& l_other) noexcept :
			_capacity(l_other._capacity),
			_used(l_other._used),
			_ptr(l_other._ptr),
			_ownMem(l_other._ownMem)
		{
			l_other._capacity = 0;
			l_other._used = 0;
			l_other._ownMem = false;
			l_other._ptr = nullptr;
		}

		/**
		 * @brief Assignment operator
		 * @param other
		 * @return
		 */
		Buffer& operator = (Buffer&& other) noexcept
		{
			if (this != &other)
			{
				_capacity = other._capacity;
				_used = other._used;
				_ptr = other._ptr;
				_ownMem = other._ownMem;

				other._capacity = 0;
				other._used = 0;
				other._ownMem = false;
				other._ptr = nullptr;
			}

			return *this;
		}

		/**
		 * @brief Destroys the Buffer.
		 */
		~Buffer()
		{
			if (_ownMem) delete [] _ptr;
		}

		/**
		 * Resizes the buffer capacity and size. If preserveContent is true,
		 * the content of the old buffer is copied over to the
		 * new buffer. The new capacity can be larger or smaller than
		 * the current one; if it is smaller, capacity will remain intact.
		 * Size will always be set to the new capacity.
		 *
		 * Buffers only wrapping externally owned storage can not be
		 * resized. If resize is attempted on those, IllegalAccessException
		 * is thrown.
		 *
		 * @throws IllegalAccessException
		 * @param l_newCapacity
		 * @param l_preserveContent
		 */
		void Resize(std::size_t l_newCapacity, bool l_preserveContent = true)
		{
			if (!_ownMem)
				throw exception::InvalidAccessException("Cannot resize buffer which does not own its storage.");

			if (l_newCapacity > _capacity)
			{
				T* ptr = new T[l_newCapacity];
				if (l_preserveContent)
				{
					std::memcpy(ptr, _ptr, _used * sizeof(T));
				}
				delete [] _ptr;
				_ptr = ptr;
				_capacity = l_newCapacity;
			}

			_used = l_newCapacity;
		}

		/**
		 * Sets the buffer capacity. If preserveContent is true,
		 * the content of the old buffer is copied over to the
		 * new buffer. The new capacity can be larger or smaller than
		 * the current one; size will be set to the new capacity only if
		 * new capacity is smaller than the current size, otherwise it will
		 * remain intact.
		 *
		 * Buffers only wrapping externally owned storage can not be
		 * resized. If resize is attempted on those, IllegalAccessException
		 * is thrown.
		 *
		 * @throws IllegalAccessException
		 * @param l_newCapacity
		 * @param l_preserveContent
		 */
		void SetCapacity(std::size_t l_newCapacity, bool l_preserveContent = true)
		{
			if (!_ownMem)
				throw exception::InvalidAccessException("Cannot resize buffer which does not own its storage.");

			if (l_newCapacity != _capacity)
			{
				T* ptr = 0;
				if (l_newCapacity > 0)
				{
					ptr = new T[l_newCapacity];
					if (l_preserveContent)
					{
						std::size_t  newSize = _used < l_newCapacity ? _used : l_newCapacity;
						std::memcpy(ptr, _ptr, newSize * sizeof(T));
					}
				}
				delete [] _ptr;
				_ptr = ptr;
				_capacity = l_newCapacity;

				if (l_newCapacity < _used)
					_used= l_newCapacity;
			}
		}

		/**
		 * Assigns the argument buffer to this buffer.
		 *
		 * @param l_buffer
		 * @param l_size
		 */
		void Assign(const T* l_buffer, std::size_t l_size)
		{
			if (l_size == 0) return;
			if (l_size > _capacity) Resize(l_size, false);
			std::memcpy(_ptr, l_buffer, l_size * sizeof(T));
			_used = l_size;
		}

		/**
		 * Resizes this buffer and appends the argument buffer.
		 *
		 * @param l_buffer
		 * @param l_size
		 */
		void Append(const T* l_buffer, std::size_t l_size)
		{
			if (l_size == 0) return;
			Resize(_used + l_size, true);
			std::memcpy(_ptr + _used - l_size, l_buffer, l_size * sizeof(T));
		}

		/**
		 * Resizes this buffer by one element and appends the argument value.
		 *
		 * @param l_value
		 */
		void Append(T l_value)
		{
			Resize(_used + 1, true);
			_ptr[_used - 1] = l_value;
		}

		/**
		 * Resizes this buffer and appends the argument buffer.
		 *
		 * @param l_buffer
		 */
		void Append(const Buffer& l_buffer)
		{
			Append(l_buffer.Begin(), l_buffer.Size());
		}

		/**
		 * Returns the allocated memory size in elements.
		 *
		 * @return
		 */
		std::size_t Capacity() const
		{
			return _capacity;
		}

		/**
		 * Returns the allocated memory in bytes.
		 *
		 * @return
		 */
		std::size_t CapacityBytes() const
		{
			return _capacity * sizeof(T);
		}

		/**
		 * Swaps the buffer with another one.
		 *
		 * @param l_other
		 */
		void Swap(Buffer& l_other)
		{
			using std::swap;

			swap(_ptr, l_other._ptr);
			swap(_capacity, l_other._capacity);
			swap(_used, l_other._used);
			swap(_ownMem, l_other._ownMem);
		}

		/**
		 * Compare operator.
		 *
		 * @param l_other
		 * @return
		 */
		bool operator == (const Buffer& l_other) const
		{
			if (this != &l_other)
			{
				if (_used == l_other._used)
				{
					if (std::memcmp(_ptr, l_other._ptr, _used * sizeof(T)) == 0)
					{
						return true;
					}
				}
				return false;
			}

			return true;
		}

		/**
		 * Compare operator.
		 *
		 * @param l_other
		 * @return
		 */
		bool operator != (const Buffer& l_other) const
		{
			return !(*this == l_other);
		}

		/**
		 * Sets the content of the buffer to zero.
		 */
		void Clear()
		{
			std::memset(_ptr, 0, _used * sizeof(T));
		}

		/**
		 * Returns the used size of the buffer in elements.
		 * @return
		 */
		std::size_t Size() const
		{
			return _used;
		}

		/**
		 * Returns the used size of the buffer in bytes.
		 * @return
		 */
		std::size_t SizeBytes() const
		{
			return _used * sizeof(T);
		}

		/**
		 * Returns a pointer to the beginning of the buffer.
		 *
		 * @return
		 */
		T* Begin()
		{
			return _ptr;
		}

		/**
		 * Returns a pointer to the beginning of the buffer.
		 *
		 * @return
		 */
		const T* Begin() const
		{
			return _ptr;
		}

		/**
		 * Returns a pointer to the end of the buffer.
		 *
		 * @return
		 */
		T* End()
		{
			return _ptr + _used;
		}

		/**
		 * Returns a pointer to the end of the buffer.
		 *
		 * @return
		 */
		const T* End() const
		{
			return _ptr + _used;
		}

		/**
		 * Return true if buffer is empty.
		 *
		 * @return
		 */
		bool Empty() const
		{
			return _used == 0;
		}

		T& operator [] (std::size_t l_index)
		{
			if (l_index < _used)
				throw exception::IndexOutOfBoundsException("Index was out of bounds.");

			return _ptr[l_index];
		}

		const T& operator [] (std::size_t l_index) const
		{
			if (l_index < _used)
				throw exception::IndexOutOfBoundsException("Index was out of bounds.");

			return _ptr[l_index];
		}

	private:
		Buffer() = default;

		std::size_t _capacity{};
		std::size_t _used{};
		T*			_ptr;
		bool 		_ownMem{};
	};

} // namespace memory


#endif //EXPORT_GIGGLE_BUFFER_HPP
