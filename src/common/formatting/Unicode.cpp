/*
* export-giggle
* Unicode.cpp
* Created by Nuno Levezinho on 24/08/2018.
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

#include "Unicode.hpp"

#include <Types.hpp>

using namespace giggle::common;
using namespace giggle::common::formatting;

typedef UInt8 	pcre_uint8;
typedef UInt16 	pcre_uint16;
typedef Int32 	pcre_int32;
typedef UInt32 	pcre_uint32;

typedef struct {
	pcre_uint8 script;		/* ucp_Arabic, etc. */
	pcre_uint8 chartype;	/* ucp_Cc, etc. (general categories) */
	pcre_uint8 gbprop;		/* ucp_gbControl, etc. (grapheme break property) */
	pcre_uint8 caseset;		/* offset to multichar other cases or zero */
	pcre_int32 other_case;	/* offset to other case, or zero if none */
} ucd_record;

extern "C" const pcre_uint32 _pcre_ucd_caseless_sets[];
extern "C" const ucd_record  _pcre_ucd_records[];
extern "C" const pcre_uint8  _pcre_ucd_stage1[];
extern "C" const pcre_uint16 _pcre_ucd_stage2[];
extern "C" const pcre_uint32 _pcre_ucp_gentype[];
extern "C" const pcre_uint32 _pcre_ucp_gbtable[];

#define UCD_BLOCK_SIZE 128
#define GET_UCD(ch) (_pcre_ucd_records + \
        _pcre_ucd_stage2[_pcre_ucd_stage1[(int)(ch) / UCD_BLOCK_SIZE] * \
        UCD_BLOCK_SIZE + (int)(ch) % UCD_BLOCK_SIZE])

#define UCD_CHARTYPE(ch)    GET_UCD(ch)->chartype
#define UCD_SCRIPT(ch)      GET_UCD(ch)->script
#define UCD_CATEGORY(ch)    _pcre_ucp_gentype[UCD_CHARTYPE(ch)]
#define UCD_GRAPHBREAK(ch)  GET_UCD(ch)->gbprop
#define UCD_CASESET(ch)     GET_UCD(ch)->caseset
#define UCD_OTHERCASE(ch)   ((pcre_uint32)((int)ch + (int)(GET_UCD(ch)->other_case)))

void giggle::common::formatting::Unicode::Properties(int l_ch, giggle::common::formatting::Unicode::CharacterProperties &l_props)
{
	// TODO: Link the missing unicode library
	/*
	if (l_ch > UCP_MAX_CODEPOINT) l_ch = 0;
	const ucd_record* ucd = GET_UCD(l_ch);
	l_props.category = static_cast<CharacterCategory>(_pcre_ucp_gentype[ucd->chartype]);
	l_props.type     = static_cast<CharacterType>(ucd->chartype);
	l_props.script   = static_cast<Script>(ucd->script);
	 */
}

int giggle::common::formatting::Unicode::ToLower(int ch)
{
	// TODO: Link the missing unicode library
	/*
	if (IsUpper(ch))
		return static_cast<int>(UCD_OTHERCASE(static_cast<unsigned>(ch)));
	else
		return ch;
	*/

	return 0;
}


int giggle::common::formatting::Unicode::ToUpper(int ch)
{
	// TODO: Link the missing unicode library
	/*
	if (IsLower(ch))
		return static_cast<int>(UCD_OTHERCASE(static_cast<unsigned>(ch)));
	else
		return ch;
	 */

	return 0;
}