#include <FluentUI/Label.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <string>
using namespace Fluentui;

Label::Label(const char* text, Widget* parent)
	: Widget(parent), font("宋体"), text(text)
{
	blob = SkTextBlob::MakeFromString(text, font.skFont());
	resize();
}

void Label::setFont(const char* fontFamily)
{
	font.setFont(fontFamily);
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
	resize();
}

void Label::setText(const char* newText)
{
	text = newText;
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
	resize();
}

void Label::setSize(size_t size)
{
	font.setSize(size);
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
	resize();
}

void Label::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(SK_ColorBLACK);
	canvas->drawTextBlob(blob, offsetX + x(), offsetY + y() + height(), paint);
}

void Label::resize() { setRect(blob->bounds().width(), blob->bounds().height()); }
