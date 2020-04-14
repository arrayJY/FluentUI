#include <FluentUI/Application.h>
#include <FluentUI/Widget.h>
#include <include/core/SkColor.h>
#include <include/core/SkCanvas.h>

Fluentui::Widget::Widget(Widget* parent)
	: gackgroundColor(SK_ColorWHITE),
	  width(WINDOW_DEFAULT_WIDTH), height(WINDOW_DEFAULT_HEIGHT), relativeX(0), relativeY(0),
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

void Fluentui::Widget::draw(SkCanvas* canvas, int offsetX, int offsetY)
{
	//Draw background
	SkPaint paint;
	paint.setColor(gackgroundColor);
	canvas->drawPaint(paint);
}

void Fluentui::Widget::render()
{
	//Draw itself
	SkCanvas* canvas = skiaContext->getCanvas();
	draw(canvas, absoluteX(), absoluteY());
	//Draw children
	for (const auto& i : children)
	{
		i->render(canvas, absoluteX(), absoluteY());
	}
	skiaContext->flush();
	glfwContext->swapBuffer();
}

void Fluentui::Widget::render(SkCanvas* canvas, const int offsetX, const int offsetY)
{
	draw(canvas, offsetX, offsetY);
	for (const auto& i : children)
	{
		i->render(canvas, offsetX + x(), offsetX + y());
	}
}

void Fluentui::Widget::show() { glfwContext->show(); }
void Fluentui::Widget::hide() { glfwContext->hide(); }
void Fluentui::Widget::close() { glfwContext->close(); }
bool Fluentui::Widget::shouldClose() { return glfwContext->shouldClose(); }
void Fluentui::Widget::setPos(int x, int y) { relativeX = x, relativeY = y; }
const int Fluentui::Widget::x() { return relativeX; }
const int Fluentui::Widget::y() { return relativeY; }
const int Fluentui::Widget::absoluteX() { return parent ? relativeX + parent->x() : relativeX; }
const int Fluentui::Widget::absoluteY() { return parent ? relativeY + parent->y() : relativeY; }
