#include <FluentUI/Button.h>
#include <include/core/SkRect.h>
#include <include/core/SkCanvas.h>
using namespace Fluentui;

Button::Button(const char* t, Widget* parent)
	: Widget(parent),
	text(t), label(nullptr),
	backgroundColor(DEFAULT_GACKGROUND_COLOR)
{
	label = new Label(t, this);
	if (text.empty())
	{
		text = "Button";
		label->setText(text.c_str());
	}
	setRect(label->width() + DEFAULT_X_PADDING, label->height() + 2 * DEFAULT_Y_PADDING);
	label->setPos(DEFAULT_X_PADDING, DEFAULT_Y_PADDING);
}

void Button::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(backgroundColor);
	SkRect rect = SkRect::MakeXYWH(offsetX + x(), offsetY + y(), width(), height());
	canvas->drawRect(rect, paint);
}
