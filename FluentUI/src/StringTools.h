#pragma once
#include <string>
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
