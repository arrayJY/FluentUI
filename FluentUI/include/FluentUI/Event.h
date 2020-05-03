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
			Input,
			KeyPress,
			KeyRelease,
			Resize
		};

		Event(Type type) : __accepted(false) { __type = type; }
		Type type() { return __type; }
		
		void accept() { __accepted = true; }
		void ignore() { __accepted = false; }
		bool accepted() const { return __accepted; }

	private:
		Type __type;
		bool __accepted;
	};
}
