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
	private:
		// Definition in advance for RAII. 
		std::unique_ptr<WidgetGLFWContext> glfwContext;
		std::unique_ptr<WidgetSkiaContext> skiaContext;

	public:
		Widget(Widget* parent = nullptr);
		virtual ~Widget();

		void show();
		void hide();
		void close();
		void render();
		bool shouldClose();

	protected:
		virtual void draw(SkCanvas*);
		Widget* parent;
		std::list<std::shared_ptr<Widget>> children;
	private:
		int width, height;
		SkColor gackgroundColor;
	};
}
