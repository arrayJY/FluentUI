#include <FluentUI/Font.h>

Fluentui::Font::Font(const char* fontFamily, size_t size)
{
	fontManager = SkFontMgr::RefDefault();
	typeface = fontManager->legacyMakeTypeface(fontFamily, fontStyle);
	font = SkFont(typeface, size, 1.0f, 0.0f);
}

SkFont& Fluentui::Font::skFont() { return font; }

void Fluentui::Font::setFont(const char* fontFamily, size_t size)
{
	typeface = fontManager->legacyMakeTypeface(fontFamily, fontStyle);
	font = SkFont(typeface, size, 1.0f, 0.0f);
}

void Fluentui::Font::setSize(size_t size) { font = font.makeWithSize(size); }