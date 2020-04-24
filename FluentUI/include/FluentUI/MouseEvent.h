#pragma once
#include <FluentUI/Event.h>

namespace Fluentui
{
	class MouseEvent : public Event
	{
	public:
		enum class MouseButton
		{
			None = 0,
			LeftButton,
			RightButton
		};
		MouseEvent(Type type, int x, int y) : Event(type) { __x = x; __y = y; __button = MouseButton::None; }
		MouseEvent(Type type, int x, int y, MouseButton b) : Event(type) { __x = x; __y = y; __button = b; }

		int x() const { return __x; }
		int y() const { return __y; }
		MouseButton button() const { return __button; }

	private:
		int __x, __y;
		MouseButton __button;
	};
}
