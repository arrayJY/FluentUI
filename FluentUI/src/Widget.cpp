#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>
#include <include/core/SkColor.h>
#include <include/core/SkCanvas.h>

Fluentui::Widget::Widget(Widget* parent)
	: gackgroundColor(SK_ColorWHITE),
	  width(WINDOW_DEFAULT_WIDTH), height(WINDOW_DEFAULT_HEIGHT),
	  glfwContext(nullptr), skiaContext(nullptr), 
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
			//Prevent child widget from creating another window
			return;
		}
	}
	//Init GLFW and skia context.
	{
		glfwContext = std::make_unique<WidgetGLFWContext>(width, height);
		skiaContext = std::make_unique<WidgetSkiaContext>(width, height);
	}
}

void Fluentui::Widget::draw(SkCanvas* canvas)
{
	//Draw background
	SkPaint paint;
	paint.setColor(gackgroundColor);
	canvas->drawPaint(paint);
}

void Fluentui::Widget::render()
{
	//Draw itself
	draw(skiaContext->getCanvas());
	//Draw children
	for (const auto& i : children)
	{
		i->draw(skiaContext->getCanvas());
	}
	skiaContext->flush();
	glfwContext->swapBuffer();
}

void Fluentui::Widget::show() { glfwContext->show(); }
void Fluentui::Widget::hide() { glfwContext->hide(); }
void Fluentui::Widget::close() { glfwContext->close(); }
bool Fluentui::Widget::shouldClose() { return glfwContext->shouldClose(); }
