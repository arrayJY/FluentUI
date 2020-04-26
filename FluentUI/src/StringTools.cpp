#include "StringTools.h"
std::u8string codepointToU8string(unsigned codepoint)
{
    if (codepoint > 0x10FFFF)
        return u8"";

	std::u8string temp;
	//U+0000~U+007F -> 1 byte: 0xxx xxxx
	if(codepoint <= 0x007F)
	{
		temp.push_back(codepoint & 0x7F);                   //0x7F = 0111 1111
	}
	//U+0080~U+07FF-> 2 bytes: 110x xxxx, 10yy yyyy
	else if (0x0080 <= codepoint && codepoint <= 0x07FF)
	{
		temp.push_back(0xC0 | ((codepoint >> 6) & 0x1F));   //0xC0 = 1100 0000, 0x1F = 0001 1111
		temp.push_back(0x80 | ( codepoint       & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
	}
	//U+0800~U+FFFF-> 3 bytes: 1110 xxxx, 10yy yyyy, 10zz zzzz
	else if (0x0080 <= codepoint && codepoint <= 0xFFFF)
	{
		temp.push_back(0xE0 | ((codepoint >> 12) & 0x0F));   //0xE0 = 1110 0000, 0x0F = 0000 1111
		temp.push_back(0x80 | ((codepoint >>  6) & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
		temp.push_back(0x80 | ( codepoint        & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
	}
	else
	//U+10000~U+10FFFFF-> 4 bytes: 1111 0xxx, 10yy yyyy, 10zz zzzz, 10mm mmmm
	{
		temp.push_back(0xF0 | ((codepoint >> 18) & 0x07));   //0xF0 = 1111 0000, 0x07 = 0000 0111
		temp.push_back(0x80 | ((codepoint >> 12) & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
		temp.push_back(0x80 | ((codepoint >>  6) & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
		temp.push_back(0x80 | ( codepoint        & 0x3F));   //0x80 = 1000 0000, 0x3F = 0011 1111
	}
	return temp;
}
std::string u8stringToString(std::u8string_view str) { return std::string(str.begin(), str.end()); }
std::string codepointToString(unsigned codepoint) { return u8stringToString(codepointToU8string(codepoint)); }
std::string u32stringToString(std::u32string_view str)
{
	std::string newStr;
	for (const auto &ch : str)
		newStr += codepointToString(static_cast<unsigned>(ch));
	return newStr;
}
std::u8string u32stringToU8string(std::u32string_view str)
{
	std::u8string newStr;
	for (const auto &ch : str)
		newStr += codepointToU8string(static_cast<unsigned>(ch));
	return newStr;
}
std::u32string u8stringToU32string(std::u8string_view str)
{
	uint32_t codepoint;
	uint32_t state = 0;
	std::u32string newStr;
	for (const auto& ch : str)
	{
		if (!decodeUTF8(&state, &codepoint, static_cast<uint32_t>(ch)))
			newStr.push_back(static_cast<char32_t>(codepoint));
	}
	return newStr;
}

//************************************************************************
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
uint32_t inline decodeUTF8(uint32_t* state, uint32_t* codep, uint32_t byte)
{
	const int UTF8_ACCEPT = 0;
	static const char8_t utf8d[] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
	7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
	8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
	0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
	0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
	0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
	1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
	1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
	1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
	};

	uint32_t type = utf8d[byte];

	*codep = (*state != UTF8_ACCEPT) ?
		(byte & 0x3fu) | (*codep << 6) :
		(0xff >> type) & (byte);

	*state = utf8d[256 + *state*16 + type];
	return *state;
}
//************************************************************************
