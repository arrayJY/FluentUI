#pragma once
#include <string>
#include <string_view>
std::u8string codepointToU8string(unsigned codepoint);
std::string u8stringToString(std::u8string_view str);
std::string codepointToString(unsigned codepoint);
std::string u32stringToString(std::u32string_view str);
std::u8string u32stringToU8string(std::u32string_view str);
