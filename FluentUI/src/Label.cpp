#include <FluentUI/Label.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <string>

Fluentui::Label::Label(const char* text, Widget* parent = nullptr)
	: Widget(parent), font("微软雅黑"), text(text),
	  relativeX(0), relativeY(0)
{
	blob = SkTextBlob::MakeFromString(text, font.skFont());
}

void Fluentui::Label::setFont(const char* fontFamily)
{
	font.setFont(fontFamily);
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
}

void Fluentui::Label::setText(const char* newText)
{
	text = newText;
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
}

void Fluentui::Label::setSize(size_t size)
{
	font.setSize(size);
	blob = SkTextBlob::MakeFromString(text.c_str(), font.skFont());
}

void Fluentui::Label::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(SK_ColorBLACK);
	canvas->drawTextBlob(blob, offsetX + x(), offsetY + y(), paint);
}