#pragma once
namespace Fluentui
{
	class Event
	{
	public:
		enum class Type
		{
			MouseMove,
			MousePress,
			MouseRelease,
			Enter,
			Leave,
		};

		Event(Type type) { __type = type; }
		Type type() { return __type; }
	private:
		Type __type;
	};
}
