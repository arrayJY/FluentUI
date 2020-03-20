#pragma once
#include <GLFW/glfw3.h>
#include <FluentUI/Application.h>
#include <include/gpu/GrContext.h>

namespace Fluentui
{
	static const int WINDOW_DEFAULT_WIDTH = 640;
	static const int WINDOW_DEFAULT_HEIGHT = 480;
	class Widget
	{
	public:
		Widget(Widget* parent = nullptr);
		~Widget();

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
		GLFWwindow* window;
		sk_sp<GrContext> context;
		sk_sp<SkSurface> surface;

		int width, height;
		SkColor gackgroundColor;

	};
}
