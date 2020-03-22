#pragma once
#include <list>
#include <GLFW/glfw3.h>

namespace Fluentui
{
	class Widget;
	class Application
	{
	public:
		Application();
		int exec();
		static void addPrimaryWindow(Widget*);

	private:
		void initGLFW();
		//Widget having no parent
		static std::list<Widget*> primaryWindows;
	};
}

