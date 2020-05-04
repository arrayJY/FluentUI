#pragma once
#include <string>
#include <FluentUI/Widget.h>
#include "../3rdparty/nano-signal-slot/nano_signal_slot.hpp"

namespace Fluentui
{
	class Label;
	class InputEvent;
	class KeyEvent;
	class TextBox : public Widget
	{
	public:
		TextBox(std::u8string_view text = u8"", Widget* parent = nullptr);
		Nano::Signal<void(std::u8string_view)> changeSignal;
	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);

		void inputEvent(InputEvent*);
		void keyPressEvent(KeyEvent*);
		void changeEvent(Event*);
		void focusEvent(Event*);

	private:
		void updateText();

		std::u32string __text;
		Label* __label;
		SkColor __borderColor;
		static int DEFAULT_WIDTH;
		static int DEFAULT_HEIGHT;

		static const SkColor DEFAULT_BORDER_COLOR = SkColorSetRGB(166, 166, 166);
		static const SkColor FOCUS_BORDER_COLOR = SK_ColorBLACK;
	};
}
