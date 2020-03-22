#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>

std::list<Fluentui::Widget*> Fluentui::Application::primaryWindows;

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

int Fluentui::Application::exec()
{
	try
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
	catch(std::runtime_error&)
	{
		return -1;
	}
	return 0;
}

void Fluentui::Application::addPrimaryWindow(Widget* window)
{
	primaryWindows.push_back(window);
}
