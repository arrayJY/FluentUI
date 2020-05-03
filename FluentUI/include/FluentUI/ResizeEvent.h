#pragma once
#include <FluentUI/Event.h>

namespace Fluentui
{
	class ResizeEvent : public Event
	{
	public:
		ResizeEvent(Event::Type type, int width, int height) : Event(type) { __width = width, __height = height; }
		int width() const { return __width; }
		int height() const { return __height; }
	private:
		int __width;
		int __height;
	};
}
