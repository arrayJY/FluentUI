#include <FluentUI/Font.h>
#include <../src/StringTools.h>
using namespace Fluentui;

const std::u8string_view Font::DEFAULT_FONT_FAMILY = u8"Microsoft Yahei";

Font::Font()
{
	__fontManager = SkFontMgr::RefDefault();
	__typeface = __fontManager->legacyMakeTypeface(u8stringToString(DEFAULT_FONT_FAMILY).c_str(), __fontStyle);
	__font = SkFont(__typeface, DEFAULT_SIZE, 1.0f, 0.0f);
}

Font::Font(std::u8string_view fontFamily, size_t size)
{
	__fontManager = SkFontMgr::RefDefault();
	__typeface = __fontManager->legacyMakeTypeface(u8stringToString(fontFamily).c_str(), __fontStyle);
	__font = SkFont(__typeface, size, 1.0f, 0.0f);
}

const SkFont& Font::skFont() const { return __font; }

void Font::setFont(std::u8string_view fontFamily, size_t size)
{
	__typeface = __fontManager->legacyMakeTypeface(u8stringToString(fontFamily).c_str(), __fontStyle);
	__font = SkFont(__typeface, size, 1.0f, 0.0f);
}

void Font::setSize(size_t size)
{
	__size = size;
	__font = __font.makeWithSize(size);
}