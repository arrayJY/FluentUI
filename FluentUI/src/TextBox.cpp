#include <FluentUI/TextBox.h>
#include <FluentUI/Label.h>
#include <FluentUI/InputEvent.h>
#include <FluentUI/KeyEvent.h>
#include <GLFW/glfw3.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkColor.h>
#include <../src/StringTools.h>
using namespace Fluentui;

int TextBox::DEFAULT_WIDTH = 150;
int TextBox::DEFAULT_HEIGHT = 20;

TextBox::TextBox(Widget* parent)
	: Widget(parent),
	__text(U"TextBox")
{
	__label = new Label("TextBox", this);
	__label->setIsAcceptFocus(false);
	setRect(DEFAULT_WIDTH, DEFAULT_HEIGHT);
	__label->setPos(2, height() - __label->height() - 1);
}

void TextBox::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	SkPaint paint;
	paint.setColor(SK_ColorBLACK);
    paint.setStyle(SkPaint::kStroke_Style);
	SkRect rect = SkRect::MakeXYWH(offsetX + x(), offsetY + y(), width(), height());
    canvas->drawRect(rect, paint);
}

void TextBox::inputEvent(InputEvent* e)
{
	__text.push_back(e->inputText());
	updateText();
}

void TextBox::keyPressEvent(KeyEvent* e)
{
	if (e->key() == GLFW_KEY_BACKSPACE)
		__text.pop_back();
	updateText();
}

void TextBox::updateText()
{
	std::string newStr;
	for (const auto& codepoint : __text)
	{
		newStr += u8stringToString(codepointToU8string(codepoint));
	}
	__label->setText(newStr.c_str());
}