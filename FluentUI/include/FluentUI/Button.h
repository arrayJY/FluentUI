#pragma once
#include <FluentUI/Widget.h>
#include <FluentUI/Label.h>
#include <include/core/SkColor.h>
#include <string>

namespace Fluentui
{
	class Button : public Widget
	{

	public:
		Button(std::u8string_view text = u8"", Widget* parent = nullptr);

		void setText(std::u8string_view text);

	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);
		void enterEvent(Event* e);
		void leaveEvent(Event* e);
		void mousePressEvent(MouseEvent* e);
		void mouseReleaseEvent(MouseEvent* e);

	private:
		Label* __label;
		SkColor __backgroundColor;

		static const int DEFAULT_X_PADDING = 5;
		static const int DEFAULT_Y_PADDING = 8;
		static const SkColor DEFAULT_GACKGROUND_COLOR = SkColorSetRGB(204, 204, 204);
		static const SkColor HOVER_GACKGROUND_COLOR = SkColorSetRGB(230, 230, 230);
		static const SkColor PRESS_GACKGROUND_COLOR = SkColorSetRGB(153, 153, 153);
	};
}
