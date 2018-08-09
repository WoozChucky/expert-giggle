/*
* export-giggle
* UUID.hpp
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

#ifndef EXPORT_GIGGLE_UUID_HPP
#define EXPORT_GIGGLE_UUID_HPP

#include <string>
#include "Types.hpp"

namespace giggle::common
{
	/**
	 * A UUID is an identifier that is unique across both space and time,
	 * with respect to the space of all UUIDs. Since a UUID is a fixed
	 * size and contains a time field, it is possible for values to
	 * rollover (around A.D. 3400, depending on the specific algorithm
	 * used). A UUID can be used for multiple purposes, from tagging
	 * objects with an extremely short lifetime, to reliably identifying
	 * very persistent objects across a network.
	 */
	class UUID
	{
	public:
		typedef enum Version
		{
			UUID_TIME_BASED      = 0x01,
			UUID_DCE_UID         = 0x02,
			UUID_NAME_BASED      = 0x03,
			UUID_RANDOM          = 0x04,
			UUID_NAME_BASED_SHA1 = 0x05
		} Version;

		/**
		 * @brief Create a nil (all zero) UUID.
		 */
		UUID();

		/**
		 * @brief Copy constructor.
		 * @param uuid Other uuid.
		 */
		UUID(const UUID& uuid);

		/**
		 * @brief Parses the UUID from a string.
		 * @param uuid the UUID
		 */
		explicit UUID(const std::string& uuid);

		/**
		 * @brief Parse the UUID from a string.
		 * @param uuid  The UUID.
		 */
		explicit UUID(const char* uuid);

		/**
		 * @brief Destroys the UUID
		 */
		~UUID();

		/**
		 * @brief Assignment operator.
		 * @param uuid Other UUID.
		 */
		UUID& operator = (const UUID& uuid);


		/**
		 * @brief Swaps the UUID with another one.
		 * @param uuid Other UUID.
		 */
		void Swap(UUID& uuid);

		/**
		 * @brief Parses the UUID from its string representation.
		 * @param uuid
		 */
		void Parse(const std::string& uuid);

		/**
		 * @brief Tries to interpret the given string as an UUID.
		 * If the UUID is syntactically valid, assigns the
		 * members and returns true. Otherwise leaves the
		 * object unchanged and returns false.
		 */
		bool TryParse(const std::string& uuid);
		///
		/**
		 * @brief Returns a string representation of the UUID consisting
		 * of groups of hexadecimal digits separated by hyphens.
		 */
		std::string ToString() const;

		/**
		 * @brief Copies the UUID (16 bytes) from a buffer or byte array.
		 * The UUID fields are expected to be
		 * stored in network byte order.
		 * The buffer doesn't need to be aligned.
		 * @param buffer
		 */
		void CopyFrom(const char* buffer);

		/**
		 * @brief Copies the UUID to the buffer. The fields
		 * are in network byte order.
		 * The buffer doesn't need to be aligned.
		 * There must have room for at least 16 bytes.
		 * @param buffer
		 */
		void CopyTo(char* buffer) const;

		/**
		 * @brief Returns the version of the UUID.
		 */
		Version version() const;

		/**
		 * @brief Returns the variant number of the UUID:
		 * - 0 reserved for NCS backward compatibility
		 * - 2 the Leach-Salz variant (used by this class)
		 * - 6 reserved, Microsoft Corporation backward compatibility
		 * - 7 reserved for future definition
		 */
		int Variant() const;

		bool operator == (const UUID& uuid) const;
		bool operator != (const UUID& uuid) const;
		bool operator <  (const UUID& uuid) const;
		bool operator <= (const UUID& uuid) const;
		bool operator >  (const UUID& uuid) const;
		bool operator >= (const UUID& uuid) const;

		/**
		 * @brief Returns true iff the UUID is nil (in other words,
		 * consists of all zeros).
		 */
		bool IsNull() const;

		/**
		 * @brief Returns a null/nil UUID.
		 */
		static const UUID& Null();

		/**
		 * @brief Returns the namespace identifier for the DNS namespace.
		 */
		static const UUID& DNS();

		/**
		 * @brief Returns the namespace identifier for the URI (former URL) namespace.
		 */
		static const UUID& URI();

		/**
		 * @brief Returns the namespace identifier for the OID namespace.
		 */
		static const UUID& OID();

		/**
		 * @brief Returns the namespace identifier for the X500 namespace.
		 */
		static const UUID& x500();

	protected:
		UUID(UInt32 timeLow, UInt32 timeMid, UInt32 timeHiAndVersion, UInt16 clockSeq, UInt8 node[]);
		UUID(const char* bytes, Version version);
		int Compare(const UUID& uuid) const;
		static void AppendHex(std::string& str, UInt8 n);
		static void AppendHex(std::string& str, UInt16 n);
		static void AppendHex(std::string& str, UInt32 n);
		static Int16 Nibble(char hex);
		void FromNetwork();
		void ToNetwork();

	private:
		UInt32 _timeLow;
		UInt16 _timeMid;
		UInt16 _timeHiAndVersion;
		UInt16 _clockSeq;
		UInt8 _node[6];

		friend class UUIDGenerator;

	};

}

#endif //EXPORT_GIGGLE_UUID_HPP
