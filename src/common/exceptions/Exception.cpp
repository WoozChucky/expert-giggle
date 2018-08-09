/*
* export-giggle
* Exception.cpp
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

#include "Exception.hpp"

using namespace giggle::common::exception;

Exception::Exception(int l_code):
	_pNested(nullptr),
	_code(l_code)
{
	AddBacktrace();
}

Exception::Exception(const std::string &l_msg, int l_code):
	_msg(l_msg),
	_pNested(nullptr),
	_code(l_code)
{
	AddBacktrace();
}

Exception::Exception(const std::string &l_msg, const std::string &l_arg, int l_code):
		_msg(l_msg),
		_pNested(nullptr),
		_code(l_code)
{
	if (!l_arg.empty())
	{
		_msg.append(": ");
		_msg.append(l_arg);
	}
	AddBacktrace();
}

Exception::Exception(const std::string &l_msg, const Exception &l_nested, int l_code):
		_msg(l_msg),
		_pNested(l_nested.Clone()),
		_code(l_code)
{
	AddBacktrace();
}

Exception::Exception(const Exception &l_exc):
	std::exception(l_exc),
	_msg(l_exc._msg),
	_code(l_exc._code)
{
	_pNested = l_exc._pNested ? l_exc._pNested->Clone() : nullptr;
}

Exception::~Exception() noexcept
{
	delete  _pNested;
}

Exception &Exception::operator=(const Exception &l_exc)
{
	if (&l_exc != this)
	{
		Exception* newPNested = l_exc._pNested ? l_exc._pNested->Clone() : nullptr;
		delete _pNested;
		_msg = l_exc._msg;
		_pNested = newPNested;
		_code = l_exc._code;
	}
	return *this;
}

const char *Exception::Name() const noexcept
{
	return "Exception";
}

const char *Exception::ClassName() const noexcept
{
	return typeid(*this).name();
}

const char *Exception::what() const noexcept
{
	return msg().c_str();
}

const Exception *Exception::Nested() const
{
	return _pNested;
}

const std::string &Exception::Message() const
{
	return _msg;
}

int Exception::Code() const
{
	return _code;
}

std::string Exception::DisplayText() const
{
	std::string txt;
	if (!_msg.empty())
	{
		txt.append(msg());
	}
	else
	{
		txt = Name();
	}
	return txt;
}

Exception *Exception::Clone() const
{
	return new Exception(*this);
}

void Exception::Rethrow() const
{
	throw *this;
}

void Exception::Message(const std::string &l_msg)
{
	_msg = l_msg;
}

void Exception::ExtendedMessage(const std::string &l_arg)
{
	if (!l_arg.empty())
	{
		if (!_msg.empty())
		{
			_msg.append(": ");
		}
		_msg.append(l_arg);
	}
}

void Exception::AddBacktrace()
{

}
