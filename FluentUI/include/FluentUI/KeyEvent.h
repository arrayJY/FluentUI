#pragma once
#include <FluentUI/Event.h>

namespace Fluentui
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(Event::Type type, int key) : Event(type) { __key = key; }
		int key() const { return __key; }
	private:
		int __key;

	};
}
