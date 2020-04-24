#include <FluentUI/Button.h>
#include <include/core/SkRect.h>
#include <include/core/SkCanvas.h>
#include <FluentUI/MouseEvent.h>
using namespace Fluentui;

Button::Button(const char* t, Widget* parent)
	: Widget(parent),
	__text(t), __label(nullptr),
	__backgroundColor(DEFAULT_GACKGROUND_COLOR)
{
	__label = new Label(t, this);
	if (__text.empty())
	{
		__text = "Button";
		__label->setText(__text.c_str());
	}
	setRect(__label->width() + DEFAULT_X_PADDING, __label->height() + 2 * DEFAULT_Y_PADDING);
	__label->setPos(DEFAULT_X_PADDING, DEFAULT_Y_PADDING);
}

void Button::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(__backgroundColor);
	SkRect rect = SkRect::MakeXYWH(offsetX + x(), offsetY + y(), width(), height());
	canvas->drawRect(rect, paint);
}

void Button::setText(const char* text)
{
	__text = text;
	__label->setText(text);
	setRect(__label->width() + 2 * DEFAULT_X_PADDING, __label->height() + 2 * DEFAULT_Y_PADDING);
}

void Button::enterEvent(Event* e) { __backgroundColor = HOVER_GACKGROUND_COLOR; }
void Button::leaveEvent(Event* e) { __backgroundColor = DEFAULT_GACKGROUND_COLOR; }
void Button::mousePressEvent(MouseEvent* e) { __backgroundColor = PRESS_GACKGROUND_COLOR; }
void Button::mouseReleaseEvent(MouseEvent* e) { __backgroundColor = HOVER_GACKGROUND_COLOR; }



