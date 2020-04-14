#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <include/gpu/GrContext.h>
#include "../../src/WidgetGLFWContext.h"
#include "../../src/WidgetSkiaContext.h"

namespace Fluentui
{
	static const int WINDOW_DEFAULT_WIDTH = 640;
	static const int WINDOW_DEFAULT_HEIGHT = 480;
	class Widget
	{
	protected:
		// Definition in advance for RAII. 
		std::unique_ptr<WidgetGLFWContext> glfwContext;
		std::unique_ptr<WidgetSkiaContext> skiaContext;

	public:
		Widget(Widget* parent = nullptr);
		virtual ~Widget() = default;

		void show();
		void hide();
		void close();
		void render();
		bool shouldClose();

		void setPos(int x, int y);
		const int x();
		const int y();

	protected:
		void render(SkCanvas*, int offsetX, int offsetY);
		virtual void draw(SkCanvas*, int offsetX, int offsetY);

		Widget* parent;
		std::list<std::shared_ptr<Widget>> children;

	private:
		const int absoluteX();
		const int absoluteY();
		int relativeX, relativeY;

		int width, height;
		SkColor gackgroundColor;
	};
}
