/*
* export-giggle
* Subject.hpp
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

#ifndef COMMON_SUBJECT_H
#define COMMON_SUBJECT_H

#include <map>
#include <boost/filesystem.hpp>

namespace giggle::common {

	template <typename Event>
	class Subject
	{
	public:
		Subject() = default;

		//Disallow copying and assigning
		Subject(const Subject&) = delete;
		Subject& operator=(const Subject&) = delete;

		template <typename Observer>
		void RegisterObserver(const Event& l_event, Observer&& l_observer)
		{
			this->m_observers_[l_event].push_back(std::forward<Observer>(l_observer));
		}

		template <typename Observer>
		void RegisterObserver(Event&& l_event, Observer&& l_observer)
		{
			this->m_observers_[std::move(l_event)].push_back(std::forward<Observer>(l_observer));
		}

		void Notify(const Event& l_event) const
		{
			try {
				for(const auto& obs : this->m_observers_.at(l_event))
					obs(); // Notify all observers
			} catch (std::exception& e) {
				throw e;
			}
		}

	private:
		std::map<Event, std::vector<std::function<void()>>> m_observers_;
	};

}

#endif //COMMON_SUBJECT_H
