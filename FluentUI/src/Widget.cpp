#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>
#include <FluentUI/MouseEvent.h>
#include <include/core/SkColor.h>
#include <include/core/SkColorSpace.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkSurface.h>
#include <include/gpu/GrContext.h>
#include <include/gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLInterface.h>
using namespace Fluentui;

Widget::Widget(Widget* parent)
	: __gackgroundColor(SK_ColorWHITE),
	__width(0), __height(0), __x(0), __y(0),
	__glfwContext(nullptr), __skiaContext(nullptr),
	__visible(false),
	  parent(parent)
{
	/*
	 * Add widget to applicaton primary window if has no parent
	 * Transfer management of lifetime to parent if it has.
	*/
	{
		if (!parent)
		{
			Application::addPrimaryWindow(this);
		}
		else
		{
			parent->children.push_back(std::shared_ptr<Widget>(this));
			return;		//Prevent child widget from creating another window
		}
	}
	//Init GLFW and skia context.
	__width = WINDOW_DEFAULT_WIDTH, __height = WINDOW_DEFAULT_HEIGHT;
	__glfwContext = std::make_unique<WindowGLFWContext>(__width, __height);
	__skiaContext = std::make_unique<WindowSkiaContext>(__width, __height);
}

void Widget::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	//Draw background
	SkPaint paint;
	paint.setColor(__gackgroundColor);
	canvas->drawPaint(paint);
}

void Widget::render(SkCanvas* canvas, const int offsetX, const int offsetY)
{
	if (!isVisible())
		return;
	//Draw itself;
	draw(canvas, offsetX, offsetY);
	//Draw children
	for (const auto& i : children)
	{
		i->render(canvas, offsetX + x(), offsetX + y());
	}
}

void Widget::show() { setVisible(true); }
void Widget::hide() { setVisible(false); }
void Widget::close() { __visible = true; }
void Widget::event(Event* event)
{
	switch (event->type())
	{
	case Event::Type::MouseMove:
		mouseMoveEvent(static_cast<MouseEvent*>(event));
		break;
	case Event::Type::Enter:
		enterEvent(event);
		break;
	case Event::Type::Leave:
		leaveEvent(event);
		break;
	case Event::Type::MousePress:
		mousePressEvent(static_cast<MouseEvent*>(event));
		break;
	case Event::Type::MouseRelease:
		mouseReleaseEvent(static_cast<MouseEvent*>(event));
		break;
	default:
		return;
	}
};

void Widget::setPos(int x, int y) { __x = x, __y = y; }
void Widget::setVisible(bool visible)
{
	__visible = visible;
	for (const auto& i : children)
	{
		i->setVisible(visible);
	}
}
void Widget::setRect(int width, int height)
{
	__width = width, __height = height;
	if (!parent)
	{
		__glfwContext->setSize(width, height);
	}
}

int Widget::x() const { return __x; }
int Widget::y() const { return __y; }
bool Widget::isVisible() const { return __visible; }
int Widget::width() const { return __width; }
int Widget::height() const { return __height; }

void Widget::mouseMoveEvent(MouseEvent*) { }
void Widget::enterEvent(Event*) { }
void Widget::leaveEvent(Event*) { }
void Widget::mousePressEvent(MouseEvent*) { }
void Widget::mouseReleaseEvent(MouseEvent*) { }

/************************ Proxy Class *************************/

Widget::WindowGLFWContext::WindowGLFWContext(int width, int height)
{
	//Create glfw window
	if (!(__window = glfwCreateWindow(width, height, "FluentUI", nullptr, nullptr)))
	{
		throw std::runtime_error("Create window failed.");
	}
	//Create glfw context
	glfwMakeContextCurrent(__window);
}

Widget::WindowGLFWContext::~WindowGLFWContext()
{
	glfwDestroyWindow(__window);
}

void Widget::WindowGLFWContext::show() { glfwShowWindow(__window); }
void Widget::WindowGLFWContext::hide() { glfwHideWindow(__window); }
void Widget::WindowGLFWContext::swapBuffer() { glfwSwapBuffers(__window); }
void Widget::WindowGLFWContext::close() { glfwSetWindowShouldClose(__window, 1); }
bool Widget::WindowGLFWContext::shouldClose() { return glfwWindowShouldClose(__window); }
GLFWwindow* Widget::WindowGLFWContext::getGLFWWindow() { return __window; }

void Widget::WindowGLFWContext::setSize(int width, int height) { glfwSetWindowSize(__window, width, height); }

Widget::WindowSkiaContext::WindowSkiaContext(int width, int height)
	: __width(width), __height(height),
	  __context(nullptr), __surface(nullptr)
{
	//Create skia OpenGL context
	{
		GrContextOptions options;
		if (!(__context = GrContext::MakeGL(nullptr, options)))
		{
			throw std::runtime_error("Create window context failed.");
		}
	}
	//Create skia surface
	{
		GrGLFramebufferInfo framebufferInfo;
		framebufferInfo.fFBOID = 0;
		framebufferInfo.fFormat = GL_RGBA8;

		SkColorType colorType = kRGBA_8888_SkColorType;

		GrBackendRenderTarget backendRenderTarget(width, height, 0, 0, framebufferInfo);

		if (!(__surface = SkSurface::MakeFromBackendRenderTarget(__context.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr)))
		{
			throw std::runtime_error("Create window surface failed.");
		}
	}
}
SkCanvas* Widget::WindowSkiaContext::getCanvas() { return __surface->getCanvas(); }
void Widget::WindowSkiaContext::flush() { __context->flush(); }
