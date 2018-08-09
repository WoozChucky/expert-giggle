/*
* export-giggle
* ThreadSafeQueue.hpp
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

#ifndef EXPORT_GIGGLE_THREADSAFEQUEUE_HPP
#define EXPORT_GIGGLE_THREADSAFEQUEUE_HPP

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>

namespace giggle::common::threading {

	template<typename T>
	class ThreadSafeQueue {

	public:

		/**
		 * Destructor
		 */
		~ThreadSafeQueue()
		{
			Invalidate();
		}

		/**
		 * Attempt to get the first value in the queue.
		 * Returns true if a value was successfully written to the out parameter, false otherwise.
		 */
		bool TryPop(T& out)
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			if(m_queue.empty() || !m_valid)
			{
				return false;
			}
			out = std::move(m_queue.front());
			m_queue.pop();
			return true;
		}

		/**
		 * Get the first value in the queue.
		 * Will block until a value is available unless clear is called or the instance is destructed.
		 * Returns true if a value was successfully written to the out parameter, false otherwise.
		 */
		bool WaitPop(T& out)
		{
			std::unique_lock<std::mutex> lock{m_mutex};
			m_condition.wait(lock, [this]()
			{
				return !m_queue.empty() || !m_valid;
			});
			/*
			 * Using the condition in the predicate ensures that spurious wakeups with a valid
			 * but empty queue will not proceed, so only need to check for validity before proceeding.
			 */
			if(!m_valid)
			{
				return false;
			}
			out = std::move(m_queue.front());
			m_queue.pop();
			return true;
		}

		/**
		 * Push a new value onto the queue.
		 */
		void Push(T value)
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			m_queue.push(std::move(value));
			m_condition.notify_one();
		}

		/**
		 * Check whether or not the queue is empty.
		 */
		bool Empty() const
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			return m_queue.empty();
		}

		/**
		 * Clear all items from the queue.
		 */
		void Clear()
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			while(!m_queue.empty())
			{
				m_queue.pop();
			}
			m_condition.notify_all();
		}

		/**
		 * Invalidate the queue.
		 * Used to ensure no conditions are being waited on in waitPop when
		 * a thread or the application is trying to exit.
		 * The queue is invalid after calling this method and it is an error
		 * to continue using a queue after this method has been called.
		 */
		void Invalidate()
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			m_valid = false;
			m_condition.notify_all();
		}

		/**
		 * Returns whether or not this queue is valid.
		 */
		bool IsValid() const
		{
			std::lock_guard<std::mutex> lock{m_mutex};
			return m_valid;
		}

	private:

		std::atomic_bool m_valid{true};
		mutable std::mutex m_mutex;
		std::queue<T> m_queue;
		std::condition_variable m_condition;

	};

} // namespace threading

#endif //EXPORT_GIGGLE_THREADSAFEQUEUE_HPP
