#pragma once
#include <list>
#include <GLFW/glfw3.h>
#include <FluentUI/Event.h>
#include <FluentUI/MouseEvent.h>

namespace Fluentui
{
	class Widget;
	class Event;
	class MouseEvent;
	class InputEvent;
	enum class Event::Type;
	enum class MouseEvent::MouseButton;
	class Application
	{
	public:
		Application();
		int exec();
		static void addPrimaryWindow(Widget*);

		static void sendEvent(Widget* recevier, Event* event);
		static void processMouseEvent(Widget*, MouseEvent*);
		static void processMouseButtonEvent(Widget*, MouseEvent*);
		static void processInputEvent(Widget*, InputEvent*);

		static void setMousePos(int x, int y);
		static int getMouseX();
		static int getMouseY();

		static Widget* focusWidget();

	private:
		static void initGLFW();

		static inline bool isPointInWidget(Widget*, int x, int y);

		//Widget having no parent
		static std::list<Widget*> primaryWindows;
		static int __lastmousePosX, __lastmousePosY;
		static Widget* __focusWidget;
	};
}

