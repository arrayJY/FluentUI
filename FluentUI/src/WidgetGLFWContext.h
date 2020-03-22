#pragma once

#include <GLFW/glfw3.h>

namespace Fluentui
{
	class WidgetGLFWContext
	{
	public:
		WidgetGLFWContext(int width, int height);
		~WidgetGLFWContext();

		void show();
		void hide();
		void close();
		void swapBuffer();
		bool shouldClose();
	private:
		GLFWwindow* window;
	};
}
