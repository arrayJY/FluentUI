#pragma once
#include <string>
#include <string_view>
std::u8string codepointToU8string(unsigned codepoint);
std::string u8stringToString(std::u8string_view str);
std::string codepointToString(unsigned codepoint);
std::string u32stringToString(std::u32string_view str);
std::u8string u32stringToU8string(std::u32string_view str);
std::u32string u8stringToU32string(std::u8string_view str);

//************************************************************************
// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.
uint32_t inline decodeUTF8(uint32_t* state, uint32_t* codep, uint32_t byte);
//************************************************************************
