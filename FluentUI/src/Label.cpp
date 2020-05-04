#include <FluentUI/Label.h>
#include <FluentUI/Event.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <../src/StringTools.h>
using namespace Fluentui;

Label::Label(std::u8string_view str, Widget* parent)
	: Widget(parent), __text(str)
{
	if (str.empty())
	{
		resize(0, Font::DEFAULT_SIZE);
		return;
	}
	blob = SkTextBlob::MakeFromString(u8stringToString(str).c_str(), font().skFont());
	__resize();
}

void Label::changeEvent(Event* e)
{
	if (__text.empty())
	{
		resize(0, Font::DEFAULT_SIZE);
		return;
	}
	if (e->type() == Event::Type::FontChange)
	{
		blob = SkTextBlob::MakeFromString(u8stringToString(__text).c_str(), font().skFont());
		__resize();
	}
}

void Label::setText(std::u8string_view newText)
{
	__text = newText;
	if (newText.empty())
	{
		resize(0, height());
		return;
	}
	blob = SkTextBlob::MakeFromString(u8stringToString(__text).c_str(), font().skFont());
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
