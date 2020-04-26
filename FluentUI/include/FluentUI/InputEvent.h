#pragma once
#include <FluentUI/Event.h>
#include <string_view>

namespace Fluentui
{
	class InputEvent : public Event
	{
	public:
		InputEvent(Event::Type t, char32_t ch) : Event(t) { __inputText = ch; }
		const char32_t inputText() { return __inputText; }
	private:
		char32_t __inputText;
	};
}
