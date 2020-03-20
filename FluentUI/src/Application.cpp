#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>

Fluentui::Application::Application()
{
	initGLFW();
}


void Fluentui::Application::initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_STENCIL_BITS, 0);
	glfwWindowHint(GLFW_DEPTH_BITS, 0);
	glfwSwapInterval(1);
}

void Fluentui::Application::exec()
{
	while (!primaryWindows.empty())
	{
		for (auto i = primaryWindows.begin(); i != primaryWindows.end(); )
		{
			auto widget = *i;
			//Render every primary windows.
			widget->render();
			//Remove window from list if it should close.
			if (widget->shouldClose())
				i = primaryWindows.erase(i);
			else
				i++;
		}
		glfwWaitEvents();
	}
}

void Fluentui::Application::addPrimaryWindow(Widget* window)
{
	primaryWindows.push_back(window);
}
