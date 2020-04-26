#pragma once
#include <FluentUI/Event.h>
#include <string_view>

namespace Fluentui
{
	class InputEvent : public Event
	{
	public:
		InputEvent(Event::Type t, const std::u8string_view str) : Event(t) { __inputString = str; }
		const std::u8string& inputString() { return __inputString; }
	private:
		std::u8string __inputString;
	};
}
