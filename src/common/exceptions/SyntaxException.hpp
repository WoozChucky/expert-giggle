/*
* export-giggle
* SyntaxException.hpp
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

#ifndef EXPORT_GIGGLE_SYNTAXEXCEPTION_HPP
#define EXPORT_GIGGLE_SYNTAXEXCEPTION_HPP

#include "DataException.hpp"

namespace giggle::common::exception
{
	class SyntaxException : public DataException
	{
	public:
		explicit SyntaxException(int l_code = 0)
				: DataException(l_code)
		{

		}

		explicit SyntaxException(const std::string &l_msg, int l_code = 0)
				: DataException(l_msg, l_code)
		{
		}

		SyntaxException(const std::string &l_msg, const std::string &l_arg, int l_code = 0)
				: DataException(l_msg, l_arg, l_code)
		{

		}

		SyntaxException(const std::string &l_msg, const Exception &l_exc, int l_code = 0)
				: DataException(l_msg, l_exc, l_code)
		{

		}

		SyntaxException(const SyntaxException &l_exc) = default;

		const char* Name() const noexcept override
		{
			return "SyntaxException";
		}
	};

} // namespace exception

#endif //EXPORT_GIGGLE_SYNTAXEXCEPTION_HPP
