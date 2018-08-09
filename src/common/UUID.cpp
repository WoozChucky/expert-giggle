/*
* export-giggle
* UUID.cpp
* Created by Nuno Levezinho on 8/9/2018.
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

#include "UUID.hpp"

#include <cstring>

#include <exceptions/Exception.hpp>
#include <ByteOrder.hpp>

using namespace giggle::common;

UUID::UUID() :
	_timeLow(0),
	_timeMid(0),
	_timeHiAndVersion(0),
	_clockSeq(0)
{
	std::memset(_node, 0, sizeof(_node));
}

UUID::UUID(const UUID &uuid) :
	_timeLow(uuid._timeLow),
	_timeMid(uuid._timeMid),
	_timeHiAndVersion(uuid._timeHiAndVersion),
	_clockSeq(uuid._clockSeq)
{
	std::memcpy(_node, uuid._node, sizeof(_node));
}

UUID::UUID(const std::string &uuid)
{
	Parse(uuid);
}

UUID::UUID(const char *uuid)
{
	Parse(std::string(uuid));
}

UUID::~UUID() = default;

UUID &UUID::operator=(const UUID &uuid)
{
	if (&uuid != this)
	{
		_timeLow = uuid._timeLow;
		_timeMid = uuid._timeMid;
		_timeHiAndVersion = uuid._timeHiAndVersion;
		_clockSeq         = uuid._clockSeq;
		std::memcpy(_node, uuid._node, sizeof(_node));
	}
	return *this;
}

void UUID::Swap(UUID &uuid)
{
	std::swap(_timeLow, uuid._timeLow);
	std::swap(_timeMid, uuid._timeMid);
	std::swap(_timeHiAndVersion, uuid._timeHiAndVersion);
	std::swap(_clockSeq, uuid._clockSeq);
	std::swap_ranges(_node, _node + 6, &uuid._node[0]);
}

void UUID::Parse(const std::string &uuid)
{
	if (!TryParse(uuid))
		throw giggle::common::exception::SyntaxException(uuid);
}

bool UUID::TryParse(const std::string &uuid)
{
	if (uuid.size() < 32)
		return false;

	bool haveHyphens = false;
	if (uuid[8] == '-' && uuid[13] == '-' && uuid[18] == '-' && uuid[23] == '-')
	{
		if (uuid.size() == 36)
			haveHyphens = true;
		else
			return false;
	}
	else if (uuid.size() != 32)
		return false;

	UUID newUUID;
	std::string::const_iterator it = uuid.begin();
	newUUID._timeLow = 0;
	for (int i = 0; i < 8; ++i)
	{
		Int16 n = Nibble(*it++);
		if (n < 0) return false;
		newUUID._timeLow = (newUUID._timeLow << 4) | n;
	}
	if (haveHyphens) ++it;
	newUUID._timeMid = 0;
	for (int i = 0; i < 4; ++i)
	{
		Int16 n = Nibble(*it++);
		if (n < 0) return false;
		newUUID._timeMid = (newUUID._timeMid << 4) | n;
	}
	if (haveHyphens) ++it;
	newUUID._timeHiAndVersion = 0;
	for (int i = 0; i < 4; ++i)
	{
		Int16 n = Nibble(*it++);
		if (n < 0) return false;
		newUUID._timeHiAndVersion = (newUUID._timeHiAndVersion << 4) | n;
	}
	if (haveHyphens) ++it;
	newUUID._clockSeq = 0;
	for (int i = 0; i < 4; ++i)
	{
		Int16 n = Nibble(*it++);
		if (n < 0) return false;
		newUUID._clockSeq = (newUUID._clockSeq << 4) | n;
	}
	if (haveHyphens) ++it;

	for (int i = 0; i < 6; ++i)
	{
		Int16 n1 = Nibble(*it++);
		if (n1 < 0) return false;
		Int16 n2 = Nibble(*it++);
		if (n2 < 0) return false;

		newUUID._node[i] = static_cast<UInt8>((n1 << 4) | n2);
	}
	Swap(newUUID);

	return true;
}

std::string UUID::ToString() const
{
	std::string result;
	result.reserve(36);
	AppendHex(result, _timeLow);
	result += '-';
	AppendHex(result, _timeMid);
	result += '-';
	AppendHex(result, _timeHiAndVersion);
	result += '-';
	AppendHex(result, _clockSeq);
	result += '-';
	for (int i = 0; i < sizeof(_node); ++i)
		AppendHex(result, _node[i]);
	return result;
}

void UUID::CopyFrom(const char *buffer)
{
	UInt32 i32;
	UInt16 i16;
	std::memcpy(&i32, buffer, sizeof(i32));
	_timeLow = ByteOrder::fromNetwork(i32);
	buffer += sizeof(i32);
	std::memcpy(&i16, buffer, sizeof(i16));
	_timeMid = ByteOrder::fromNetwork(i16);
	buffer += sizeof(i16);
	std::memcpy(&i16, buffer, sizeof(i16));
	_timeHiAndVersion = ByteOrder::fromNetwork(i16);
	buffer += sizeof(i16);
	std::memcpy(&i16, buffer, sizeof(i16));
	_clockSeq = ByteOrder::fromNetwork(i16);
	buffer += sizeof(i16);
	std::memcpy(_node, buffer, sizeof(_node));
}

void UUID::CopyTo(char *buffer) const
{
	UInt32 i32 = ByteOrder::toNetwork(_timeLow);
	std::memcpy(buffer, &i32, sizeof(i32));
	buffer += sizeof(i32);
	UInt16 i16 = ByteOrder::toNetwork(_timeMid);
	std::memcpy(buffer, &i16, sizeof(i16));
	buffer += sizeof(i16);
	i16 = ByteOrder::toNetwork(_timeHiAndVersion);
	std::memcpy(buffer, &i16, sizeof(i16));
	buffer += sizeof(i16);
	i16 = ByteOrder::toNetwork(_clockSeq);
	std::memcpy(buffer, &i16, sizeof(i16));
	buffer += sizeof(i16);
	std::memcpy(buffer, _node, sizeof(_node));
}

UUID::Version UUID::version() const
{
	return Version(_timeHiAndVersion >> 12);
}

int UUID::Variant() const
{
	int v = _clockSeq >> 13;
	if ((v & 6) == 6)
		return v;
	else if (v & 4)
		return 2;
	else
		return 0;
}

bool UUID::operator==(const UUID &uuid) const
{
	return Compare(uuid) == 0;
}

bool UUID::operator!=(const UUID &uuid) const
{
	return Compare(uuid) != 0;
}

bool UUID::operator<(const UUID &uuid) const
{
	return Compare(uuid) < 0;
}

bool UUID::operator<=(const UUID &uuid) const
{
	return Compare(uuid) <= 0;
}

bool UUID::operator>(const UUID &uuid) const
{
	return Compare(uuid) > 0;
}

bool UUID::operator>=(const UUID &uuid) const
{
	return Compare(uuid) >= 0;
}

bool UUID::IsNull() const
{
	return Compare(Null()) == 0;
}

UUID::UUID(UInt32 timeLow, UInt32 timeMid, UInt32 timeHiAndVersion, UInt16 clockSeq, UInt8 *node) :
	_timeLow(static_cast<UInt16>(timeLow)),
	_timeMid(static_cast<UInt16>(timeMid)),
	_timeHiAndVersion(static_cast<UInt16>(timeHiAndVersion)),
	_clockSeq(clockSeq)
{
	std::memcpy(_node, node, sizeof(_node));
}

UUID::UUID(const char *bytes, Version version)
{
	UInt32 i32;
	UInt16 i16;
	std::memcpy(&i32, bytes, sizeof(i32));
	_timeLow = ByteOrder::fromNetwork(i32);
	bytes += sizeof(i32);
	std::memcpy(&i16, bytes, sizeof(i16));
	_timeMid = ByteOrder::fromNetwork(i16);
	bytes += sizeof(i16);
	std::memcpy(&i16, bytes, sizeof(i16));
	_timeHiAndVersion = ByteOrder::fromNetwork(i16);
	bytes += sizeof(i16);
	std::memcpy(&i16, bytes, sizeof(i16));
	_clockSeq = ByteOrder::fromNetwork(i16);
	bytes += sizeof(i16);
	std::memcpy(_node, bytes, sizeof(_node));

	_timeHiAndVersion &= 0x0FFF;
	_timeHiAndVersion |= (version << 12);
	_clockSeq &= 0x3FFF;
	_clockSeq |= 0x8000;
}

int UUID::Compare(const UUID &uuid) const
{
	if (_timeLow != uuid._timeLow) return _timeLow < uuid._timeLow ? -1 : 1;
	if (_timeMid != uuid._timeMid) return _timeMid < uuid._timeMid ? -1 : 1;
	if (_timeHiAndVersion != uuid._timeHiAndVersion) return _timeHiAndVersion < uuid._timeHiAndVersion ? -1 : 1;
	if (_clockSeq != uuid._clockSeq) return _clockSeq < uuid._clockSeq ? -1 : 1;
	for (int i = 0; i < sizeof(_node); ++i)
	{
		if (_node[i] < uuid._node[i])
			return -1;
		else if (_node[i] > uuid._node[i])
			return 1;
	}
	return 0;
}

void UUID::AppendHex(std::string &str, UInt8 n)
{
	static const char* digits = "0123456789abcdef";
	str += digits[(n >> 4) & 0xF];
	str += digits[n & 0xF];
}

void UUID::AppendHex(std::string &str, UInt16 n)
{
	AppendHex(str, UInt8(n >> 8));
	AppendHex(str, UInt8(n & 0xFF));
}

void UUID::AppendHex(std::string &str, UInt32 n)
{
	AppendHex(str, UInt16(n >> 16));
	AppendHex(str, UInt16(n & 0xFFFF));
}

Int16 UUID::Nibble(char hex)
{
	if (hex >= 'a' && hex <= 'f')
		return static_cast<Int16>(hex - 'a' + 10);
	else if (hex >= 'A' && hex <= 'F')
		return static_cast<Int16>(hex - 'A' + 10);
	else if (hex >= '0' && hex <= '9')
		return hex - '0';
	else
		return -1;
}

void UUID::FromNetwork()
{
	_timeLow = ByteOrder::fromNetwork(_timeLow);
	_timeMid = ByteOrder::fromNetwork(_timeMid);
	_timeHiAndVersion = ByteOrder::fromNetwork(_timeHiAndVersion);
	_clockSeq = ByteOrder::fromNetwork(_clockSeq);
}

void UUID::ToNetwork()
{
	_timeLow = ByteOrder::toNetwork(_timeLow);
	_timeMid = ByteOrder::toNetwork(_timeMid);
	_timeHiAndVersion = ByteOrder::toNetwork(_timeHiAndVersion);
	_clockSeq = ByteOrder::toNetwork(_clockSeq);
}

namespace
{
	static UUID uuidNull;
	static UUID uuidDNS("6ba7b810-9dad-11d1-80b4-00c04fd430c8");
	static UUID uuidURI("6ba7b811-9dad-11d1-80b4-00c04fd430c8");
	static UUID uuidOID("6ba7b812-9dad-11d1-80b4-00c04fd430c8");
	static UUID uuidX500("6ba7b814-9dad-11d1-80b4-00c04fd430c8");
}

const UUID &UUID::Null()
{
	return uuidNull;
}

const UUID &UUID::DNS()
{
	return uuidDNS;
}

const UUID &UUID::URI()
{
	return uuidURI;
}

const UUID &UUID::OID()
{
	return uuidOID;
}

const UUID &UUID::x500()
{
	return uuidX500;
}
