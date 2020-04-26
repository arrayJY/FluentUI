#include <unordered_map>
#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>
#include <FluentUI/Event.h>
#include <FluentUI/MouseEvent.h>
#include <FluentUI/InputEvent.h>
#include <FluentUI/KeyEvent.h>
using namespace Fluentui;

std::list<Widget*> Application::primaryWindows;
static std::unordered_map<GLFWwindow*, Widget*> windowToWidgetMap;
int Application::__lastmousePosX = 0;
int Application::__lastmousePosY = 0;
Widget* Application::__focusWidget = nullptr;

static void mouseMoveCallback(GLFWwindow* window, double x, double y);
static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
static void inputCallback(GLFWwindow* window, unsigned codepoint);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Application::Application()
{
	initGLFW();
}

void Application::initGLFW()
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

int Application::exec()
{
	for (auto& i : primaryWindows)
	{
		GLFWwindow* window = i->__glfwContext->getGLFWWindow();
		windowToWidgetMap[window] = i;
		glfwSetCursorPosCallback(window, mouseMoveCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetCharCallback(window, inputCallback);
		glfwSetKeyCallback(window, keyCallback);
	}
	try
	{
		while (!primaryWindows.empty())
		{
			for (auto i = primaryWindows.begin(); i != primaryWindows.end(); )
			{
				auto widget = *i;
				//Render every primary windows.
				widget->render(widget->__skiaContext->getCanvas(), widget->x(), widget->y());
				widget->__skiaContext->flush();
				widget->__glfwContext->swapBuffer();
				//Remove window from list if it should close.
				if (widget->__glfwContext->shouldClose())
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

void Application::addPrimaryWindow(Widget* window)
{
	primaryWindows.push_back(window);
}


void Application::sendEvent(Widget* recevier, Event* event)
{
	recevier->event(event);
}

void Application::processMouseEvent(Widget* recevier, MouseEvent* event)
{
	//recursive send event to children which are under the mouse
	for (auto& i : recevier->children)
	{
		if (isPointInWidget(i.get(), event->x(), event->y()))
		{
			processMouseEvent(i.get(), event);
			continue;
		}
		//send leave event
		if (isPointInWidget(i.get(), __lastmousePosX, __lastmousePosY))
		{
			Event leaveEvent(MouseEvent::Type::Leave);
			sendEvent(i.get(), &leaveEvent);
		}

	}
	sendEvent(recevier, event);
	if (!isPointInWidget(recevier, __lastmousePosX, __lastmousePosY))
	{
		Event enterEvent(MouseEvent::Type::Enter);
		sendEvent(recevier, &enterEvent);
	}
}

void Application::processMouseButtonEvent(Widget* recevier, MouseEvent* event)
{
	for (auto& child: recevier->children)
	{
		if (isPointInWidget(child.get(), getMouseX(), getMouseY()))
		{
			processMouseButtonEvent(child.get(), event);
		}
	}
	if (event->accepted())
		return;

	event->accept();
	sendEvent(recevier, event);

	//set widget focus
	if (!recevier->isAcceptFocus())
		return;
	if (__focusWidget)
		__focusWidget->clearFocus();
	__focusWidget = recevier;
	recevier->setFocus();
}

void Application::processInputEvent(Widget* recevier, InputEvent* event)
{
	sendEvent(recevier, event);
}

void Application::processKeyEvent(Widget* recevier, KeyEvent* event)
{
	sendEvent(recevier, event);
}

void Application::setMousePos(int x, int y) { __lastmousePosX = x, __lastmousePosY = y; }
int Application::getMouseX() { return __lastmousePosX; }
int Application::getMouseY() { return __lastmousePosY; }

Widget* Application::focusWidget() { return __focusWidget; }

inline bool Application::isPointInWidget(Widget* w, int x, int y)
{
	int parentGlobalX = 0, parentGlobalY = 0;
	Widget* temp = w;
	while (temp = temp->parent)
		parentGlobalX += temp->x(), parentGlobalY + temp->y();

	return x > w->x() + parentGlobalX &&
		y > w->y() + parentGlobalY &&
		x < w->x() + w->width() + parentGlobalX &&
		y < w->y() + w->height() + parentGlobalY;
}

void mouseMoveCallback(GLFWwindow* window, double x, double y)
{
	MouseEvent e(Event::Type::MouseMove, x, y);
	Application::processMouseEvent(windowToWidgetMap[window], &e);
	Application::setMousePos(x, y);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	auto mouseButton = MouseEvent::MouseButton::LeftButton;
	auto type = Event::Type::MousePress;

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		mouseButton = MouseEvent::MouseButton::RightButton;
	if (action == GLFW_RELEASE)
		type = Event::Type::MouseRelease;

	MouseEvent event(type, Application::getMouseX(), Application::getMouseY());
	Application::processMouseButtonEvent(windowToWidgetMap[window], &event);
}


void inputCallback(GLFWwindow* window, unsigned codepoint)
{
	char32_t ch = static_cast<char32_t>(codepoint);
	InputEvent e(Event::Type::Input, ch);
	Widget* recevier = Application::focusWidget() ? Application::focusWidget() : windowToWidgetMap[window];
	Application::processInputEvent(recevier, &e);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto type = Event::Type::KeyPress;
	if (action == GLFW_RELEASE)
		type = Event::Type::KeyRelease;
	Widget* recevier = Application::focusWidget() ? Application::focusWidget() : windowToWidgetMap[window];
	KeyEvent event(type, key);
	Application::processKeyEvent(recevier, &event);
}
