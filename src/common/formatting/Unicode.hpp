/*
* export-giggle
* Unicode.hpp
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

#ifndef EXPORT_GIGGLE_UNICODE_HPP
#define EXPORT_GIGGLE_UNICODE_HPP

namespace giggle::common::formatting
{
	/**
	 * This class contains enumerations and static
	 * utility functions for dealing with Unicode characters
	 * and their properties.
	 *
	 * The implementation is based on the Unicode support
	 * functions in PCRE.
	 */
	class Unicode
	{
	public:

		/**
		 * The following definitions must be kept in sync
		 * with those from the PRCE.
		 *
		 * Unicode character categories.
		 */
		enum CharacterCategory
		{
			UCP_OTHER,
			UCP_LETTER,
			UCP_MARK,
			UCP_NUMBER,
			UCP_PUNCTUATION,
			UCP_SYMBOL,
			UCP_SEPARATOR
		};

		/**
		 * Unicode character types.
		 */
		enum CharacterType
		{
			UCP_CONTROL,
			UCP_FORMAT,
			UCP_UNASSIGNED,
			UCP_PRIVATE_USE,
			UCP_SURROGATE,
			UCP_LOWER_CASE_LETTER,
			UCP_MODIFIER_LETTER,
			UCP_OTHER_LETTER,
			UCP_TITLE_CASE_LETTER,
			UCP_UPPER_CASE_LETTER,
			UCP_SPACING_MARK,
			UCP_ENCLOSING_MARK,
			UCP_NON_SPACING_MARK,
			UCP_DECIMAL_NUMBER,
			UCP_LETTER_NUMBER,
			UCP_OTHER_NUMBER,
			UCP_CONNECTOR_PUNCTUATION,
			UCP_DASH_PUNCTUATION,
			UCP_CLOSE_PUNCTUATION,
			UCP_FINAL_PUNCTUATION,
			UCP_INITIAL_PUNCTUATION,
			UCP_OTHER_PUNCTUATION,
			UCP_OPEN_PUNCTUATION,
			UCP_CURRENCY_SYMBOL,
			UCP_MODIFIER_SYMBOL,
			UCP_MATHEMATICAL_SYMBOL,
			UCP_OTHER_SYMBOL,
			UCP_LINE_SEPARATOR,
			UCP_PARAGRAPH_SEPARATOR,
			UCP_SPACE_SEPARATOR
		};

		/**
		 * Unicode 7.0 script identifiers.
		 */
		enum Script
		{

			UCP_ARABIC,
			UCP_ARMENIAN,
			UCP_BENGALI,
			UCP_BOPOMOFO,
			UCP_BRAILLE,
			UCP_BUGINESE,
			UCP_BUHID,
			UCP_CANADIAN_ABORIGINAL,
			UCP_CHEROKEE,
			UCP_COMMON,
			UCP_COPTIC,
			UCP_CYPRIOT,
			UCP_CYRILLIC,
			UCP_DESERET,
			UCP_DEVANAGARI,
			UCP_ETHIOPIC,
			UCP_GEORGIAN,
			UCP_GLAGOLITIC,
			UCP_GOTHIC,
			UCP_GREEK,
			UCP_GUJARATI,
			UCP_GURMUKHI,
			UCP_HAN,
			UCP_HANGUL,
			UCP_HANUNOO,
			UCP_HEBREW,
			UCP_HIRAGANA,
			UCP_INHERITED,
			UCP_KANNADA,
			UCP_KATAKANA,
			UCP_KHAROSHTHI,
			UCP_KHMER,
			UCP_LAO,
			UCP_LATIN,
			UCP_LIMBU,
			UCP_LINEAR_B,
			UCP_MALAYALAM,
			UCP_MONGOLIAN,
			UCP_MYANMAR,
			UCP_NEW_TAI_LUE,
			UCP_OGHAM,
			UCP_OLD_ITALIC,
			UCP_OLD_PERSIAN,
			UCP_ORIYA,
			UCP_OSMANYA,
			UCP_RUNIC,
			UCP_SHAVIAN,
			UCP_SINHALA,
			UCP_SYLOTI_NAGRI,
			UCP_SYRIAC,
			UCP_TAGALOG,
			UCP_TAGBANWA,
			UCP_TAI_LE,
			UCP_TAMIL,
			UCP_TELUGU,
			UCP_THAANA,
			UCP_THAI,
			UCP_TIBETAN,
			UCP_TIFINAGH,
			UCP_UGARITIC,
			UCP_YI,
			// Unicode 5.0
					UCP_BALINESE,
			UCP_CUNEIFORM,
			UCP_NKO,
			UCP_PHAGS_PA,
			UCP_PHOENICIAN,
			// Unicode 5.1
					UCP_CARIAN,
			UCP_CHAM,
			UCP_KAYAH_LI,
			UCP_LEPCHA,
			UCP_LYCIAN,
			UCP_LYDIAN,
			UCP_OL_CHIKI,
			UCP_REJANG,
			UCP_SAURASHTRA,
			UCP_SUNDANESE,
			UCP_VAI,
			// Unicode 5.2
					UCP_AVESTAN,
			UCP_BAMUM,
			UCP_EGYPTIAN_HIEROGLYPHS,
			UCP_IMPERIAL_ARAMAIC,
			UCP_INSCRIPTIONAL_PAHLAVI,
			UCP_INSCRIPTIONAL_PARTHIAN,
			UCP_JAVANESE,
			UCP_KAITHI,
			UCP_LISU,
			UCP_MEETEI_MAYEK,
			UCP_OLD_SOUTH_ARABIAN,
			UCP_OLD_TURKIC,
			UCP_SAMARITAN,
			UCP_TAI_THAM,
			UCP_TAI_VIET,
			// Unicode 6.0
					UCP_BATAK,
			UCP_BRAHMI,
			UCP_MANDAIC,
			// Unicode 6.1
					UCP_CHAKMA,
			UCP_MEROITIC_CURSIVE,
			UCP_MEROITIC_HIEROGLYPHS,
			UCP_MIAO,
			UCP_SHARADA,
			UCP_SORA_SOMPENG,
			UCP_TAKRI,
			// Unicode 7.0
					UCP_BASSA_VAH,
			UCP_CAUCASIAN_ALBANIAN,
			UCP_DUPLOYAN,
			UCP_ELBASAN,
			UCP_GRANTHA,
			UCP_KHOJKI,
			UCP_KHUDAWADI,
			UCP_LINEAR_A,
			UCP_MAHAJANI,
			UCP_MANICHAEAN,
			UCP_MENDE_KIKAKUI,
			UCP_MODI,
			UCP_MRO,
			UCP_NABATAEAN,
			UCP_OLD_NORTH_ARABIAN,
			UCP_OLD_PERMIC,
			UCP_PAHAWH_HMONG,
			UCP_PALMYRENE,
			UCP_PSALTER_PAHLAVI,
			UCP_PAU_CIN_HAU,
			UCP_SIDDHAM,
			UCP_TIRHUTA,
			UCP_WARANG_CITI
		};

		enum
		{
			UCP_MAX_CODEPOINT = 0x10FFFF
		};

		/**
		 * @brief This structure holds the character properties for
		 * the character with the given Unicode value.
		 */
		struct CharacterProperties
		{
			CharacterCategory   category;
			CharacterType  		type;
			Script  			script;
		};

		/**
		 * Return the Unicode character properties for the
		 * character with the given Unicode value.
		 *
		 * @param l_ch
		 * @param l_props
		 */
		static void Properties(int l_ch, CharacterProperties& l_props);

		/**
		 * Returns true if the given character is a separator.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsSpace(int l_ch);

		/**
		 * Returns true if the given character is a numeric character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsDigit(int l_ch);

		/**
		 * Returns true if the given character is a punctuation character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsPunct(int l_ch);

		/**
		 * Returns true if the given character is a letter.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsAlpha(int l_ch);

		/**
		 * Returns true if the given character is a lowercase alphabetic character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsLower(int l_ch);

		/**
		 * Returns true if the given character is a uppercase alphabetic character.
		 *
		 * @param l_ch
		 * @return
		 */
		static bool IsUpper(int l_ch);

		/**
		 * If the given character is an uppercase character,
		 * return its lowercase counterpart, otherwise return
		 * the character.
		 *
		 * @param l_ch
		 * @return
		 */
		static int ToLower(int l_ch);

		/**
		 * If the given character is a lowercase character,
		 * return its uppercase counterpart, otherwise return
		 * the character.
		 *
		 * @param l_ch
		 * @return
		 */
		static int ToUpper(int l_ch);
	};



	inline bool Unicode::IsSpace(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_SEPARATOR;
	}


	inline bool Unicode::IsDigit(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_NUMBER;
	}


	inline bool Unicode::IsPunct(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_PUNCTUATION;
	}


	inline bool Unicode::IsAlpha(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_LETTER;
	}


	inline bool Unicode::IsLower(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_LETTER && props.type == UCP_LOWER_CASE_LETTER;
	}


	inline bool Unicode::IsUpper(int l_ch)
	{
		CharacterProperties props{};
		Properties(l_ch, props);
		return props.category == UCP_LETTER && props.type == UCP_UPPER_CASE_LETTER;
	}


} // namespace formatting

#endif //EXPORT_GIGGLE_UNICODE_HPP
