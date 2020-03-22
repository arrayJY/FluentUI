#include "WidgetGLFWContext.h"
#include <stdexcept>

Fluentui::WidgetGLFWContext::WidgetGLFWContext(int width, int height)
{
	//Create glfw window
	window = glfwCreateWindow(width, height, "FluentUI", nullptr, nullptr);
	if (!window)
	{
		throw std::runtime_error("Create window failed.");
	}
	//Create glfw context
	glfwMakeContextCurrent(window);
}

Fluentui::WidgetGLFWContext::~WidgetGLFWContext()
{
	glfwDestroyWindow(window);
}

void Fluentui::WidgetGLFWContext::show() { glfwShowWindow(window); }
void Fluentui::WidgetGLFWContext::hide() { glfwHideWindow(window); }
void Fluentui::WidgetGLFWContext::swapBuffer() { glfwSwapBuffers(window); }
void Fluentui::WidgetGLFWContext::close() { glfwSetWindowShouldClose(window, 1); }
bool Fluentui::WidgetGLFWContext::shouldClose() { return glfwWindowShouldClose(window); }