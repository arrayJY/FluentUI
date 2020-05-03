#include <FluentUI/Button.h>
#include <include/core/SkRect.h>
#include <include/core/SkCanvas.h>
#include <FluentUI/MouseEvent.h>
using namespace Fluentui;

Button::Button(std::u8string_view text, Widget* parent)
	: Widget(parent),
	__label(nullptr),
	__backgroundColor(DEFAULT_GACKGROUND_COLOR)
{
	if (text.empty())
		__label = new Label(u8"Button", this);
	else
		__label = new Label(text, this);
	resize(__label->width() + DEFAULT_X_PADDING, __label->height() + 2 * DEFAULT_Y_PADDING);
	__label->setPos(DEFAULT_X_PADDING, DEFAULT_Y_PADDING);
	__label->setIsAcceptFocus(false);
}

void Button::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(__backgroundColor);
	SkRect rect = SkRect::MakeXYWH(offsetX + x(), offsetY + y(), width(), height());
	canvas->drawRect(rect, paint);
}

void Button::setText(std::u8string_view text)
{
	__label->setText(text);
	resize(__label->width() + 2 * DEFAULT_X_PADDING, __label->height() + 2 * DEFAULT_Y_PADDING);
}

void Button::enterEvent(Event* e) { __backgroundColor = HOVER_GACKGROUND_COLOR; }
void Button::leaveEvent(Event* e) { __backgroundColor = DEFAULT_GACKGROUND_COLOR; }
void Button::mousePressEvent(MouseEvent* e) { __backgroundColor = PRESS_GACKGROUND_COLOR; }
void Button::mouseReleaseEvent(MouseEvent* e) { __backgroundColor = HOVER_GACKGROUND_COLOR; }



