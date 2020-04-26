#pragma once
#include <string>
#include <FluentUI/Widget.h>

namespace Fluentui
{
	class Label;
	class InputEvent;
	class KeyEvent;
	class TextBox : public Widget
	{
	public:
		TextBox(Widget* parent);
	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);

		void inputEvent(InputEvent*);
		void keyPressEvent(KeyEvent*);

	private:
		void updateText();

		std::u32string __text;
		Label* __label;
		static int DEFAULT_WIDTH;
		static int DEFAULT_HEIGHT;
	};
}
