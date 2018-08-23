/*
* export-giggle
* LogicException.hpp
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

#ifndef EXPORT_GIGGLE_LOGICEXCEPTION_HPP
#define EXPORT_GIGGLE_LOGICEXCEPTION_HPP

#include "Exception.hpp"

namespace giggle::common::exception
{
	class LogicException : public Exception
	{
	public:
		explicit LogicException(int l_code = 0)
				: Exception(l_code)
		{

		}

		explicit LogicException(const std::string &l_msg, int l_code = 0)
				: Exception(l_msg, l_code)
		{
		}

		LogicException(const std::string &l_msg, const std::string &l_arg, int l_code = 0)
				: Exception(l_msg, l_arg, l_code)
		{

		}

		LogicException(const std::string &l_msg, const Exception &l_exc, int l_code = 0)
				: Exception(l_msg, l_exc, l_code)
		{

		}

		LogicException(const LogicException &l_exc)	= default;

		const char* Name() const noexcept override
		{
			return "LogicException";
		}
	};

} // namespace exception

#endif //EXPORT_GIGGLE_LOGICEXCEPTION_HPP
