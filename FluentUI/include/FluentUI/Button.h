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
		Button(const char* text, Widget* parent = nullptr);

	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);

	private:
		std::string text;
		Label* label;
		SkColor backgroundColor;

		static const int DEFAULT_X_PADDING = 5;
		static const int DEFAULT_Y_PADDING = 8;
		static const SkColor DEFAULT_GACKGROUND_COLOR = SkColorSetRGB(204, 204, 204);

	};
}
