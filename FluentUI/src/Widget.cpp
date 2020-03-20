#include <FluentUI/Widget.h>
#include <FluentUI/Application.h>
#include <include/core/SkColor.h>
#include <include/core/SkColorSpace.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkSurface.h>
#include <include/gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLInterface.h>


Fluentui::Widget::Widget(Widget* parent)
	: gackgroundColor(SK_ColorWHITE),
	  context(nullptr), surface(nullptr),
	  width(WINDOW_DEFAULT_WIDTH), height(WINDOW_DEFAULT_HEIGHT),
	  parent(nullptr)
{
	//Create glfw window
	{
		window = glfwCreateWindow(width, height, "FluentUI", nullptr, nullptr);
		if (!window)
		{
			throw std::runtime_error("Create window failed.");
		}
		glfwMakeContextCurrent(window);
	}
	//Create skia OpenGL context
	{
		GrContextOptions options;
		context = GrContext::MakeGL(nullptr, options);
		if (!context)
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

		surface = SkSurface::MakeFromBackendRenderTarget(context.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr);
		if (!surface)
		{
			throw std::runtime_error("Create window surface failed.");
		}
	}
	
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
			this->parent = parent;
			this->parent->children.push_back(std::shared_ptr<Widget>(this));
		}
	}
}

void Fluentui::Widget::draw(SkCanvas* canvas)
{
	//Draw background
	SkPaint paint;
	paint.setColor(gackgroundColor);
	canvas->drawPaint(paint);
}

void Fluentui::Widget::show()
{
	glfwShowWindow(window);
}
void Fluentui::Widget::hide()
{
	glfwHideWindow(window);
}
void Fluentui::Widget::close()
{
	return glfwSetWindowShouldClose(window, 1);
}

void Fluentui::Widget::render()
{
	//Draw itself
	draw(surface->getCanvas());
	//Draw children
	for (const auto& i : children)
	{
		i->draw(surface->getCanvas());
	}
	context->flush();
	glfwSwapBuffers(window);
}
bool Fluentui::Widget::shouldClose()
{ 
	return glfwWindowShouldClose(window); 
}

Fluentui::Widget::~Widget()
{
	glfwDestroyWindow(window);
}
