#include <FluentUI/Font.h>
#include <../src/StringTools.h>

Fluentui::Font::Font(std::u8string_view fontFamily, size_t size)
{
	fontManager = SkFontMgr::RefDefault();
	typeface = fontManager->legacyMakeTypeface(u8stringToString(fontFamily).c_str(), fontStyle);
	font = SkFont(typeface, size, 1.0f, 0.0f);
}

SkFont& Fluentui::Font::skFont() { return font; }

void Fluentui::Font::setFont(std::u8string_view fontFamily, size_t size)
{
	typeface = fontManager->legacyMakeTypeface(u8stringToString(fontFamily).c_str(), fontStyle);
	font = SkFont(typeface, size, 1.0f, 0.0f);
}

void Fluentui::Font::setSize(size_t size) { font = font.makeWithSize(size); }