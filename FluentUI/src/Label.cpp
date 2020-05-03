#include <FluentUI/Label.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <../src/StringTools.h>
using namespace Fluentui;

const std::u8string_view Label::DEFAULT_FONT = u8"宋体";

Label::Label(std::u8string_view str, Widget* parent)
	: Widget(parent), font(DEFAULT_FONT), __text(str)
{
	if (str.empty())
	{
		resize(0, Font::DEFAULT_SIZE);
		return;
	}
	blob = SkTextBlob::MakeFromString(u8stringToString(str).c_str(), font.skFont());
	__resize();
}

void Label::setFont(std::u8string_view fontFamily)
{
	font.setFont(fontFamily);
	blob = SkTextBlob::MakeFromString(u8stringToString(__text).c_str(), font.skFont());
	__resize();
}

void Label::setText(std::u8string_view newText)
{
	__text = newText;
	if (newText.empty())
	{
		resize(0, height());
		return;
	}
	blob = SkTextBlob::MakeFromString(u8stringToString(__text).c_str(), font.skFont());
	__resize();
}

void Label::setSize(size_t size)
{
	font.setSize(size);
	blob = SkTextBlob::MakeFromString(u8stringToString(__text).c_str(), font.skFont());
	__resize();
}

void Label::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	if (__text.empty())
		return;
	SkPaint paint;
	paint.setColor(SK_ColorBLACK);
	canvas->drawTextBlob(blob, offsetX + x(), offsetY + y() + height(), paint);
}

void Label::__resize() { resize(blob->bounds().width(), blob->bounds().height()); }

const std::u8string_view Label::text() { return __text; }
