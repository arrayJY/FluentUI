#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include <include/core/SkSurface.h>
#include <include/gpu/GrContext.h>

namespace Fluentui
{
	static const int WINDOW_DEFAULT_WIDTH = 640;
	static const int WINDOW_DEFAULT_HEIGHT = 480;

	class Application;
	class Event;
	class MouseEvent;
	class Widget
	{
	public:
		class WindowGLFWContext
		{
		public:
			WindowGLFWContext(int width, int height);
			~WindowGLFWContext();

			void show();
			void hide();
			void close();
			void swapBuffer();
			bool shouldClose();

			void setSize(int width, int height);

			GLFWwindow* getGLFWWindow();
		private:
			GLFWwindow* __window;
		};

		class WindowSkiaContext
		{
		public:
			WindowSkiaContext(int width, int height);
			~WindowSkiaContext() = default;
			SkCanvas* getCanvas();
			void flush();

		private:
			sk_sp<GrContext> __context;
			sk_sp<SkSurface> __surface;
			int __width, __height;
		};
	private:
		// Definition in advance for RAII. 
		std::unique_ptr<WindowGLFWContext> __glfwContext;
		std::unique_ptr<WindowSkiaContext> __skiaContext;
	public:
		Widget(Widget* parent = nullptr);
		virtual ~Widget() = default;

		void show();
		void hide();
		void close();
		void render(SkCanvas*, int offsetX, int offsetY);

		void setVisible(bool visible);
		void setPos(int x, int y);
		void setRect(int width, int height);

		int x() const;
		int y() const;
		int width() const;
		int height() const;
		bool isVisible() const;

	protected:
		virtual void draw(SkCanvas*, int offsetX, int offsetY);

		Widget* parent;
		std::list<std::shared_ptr<Widget>> children;

	private:
		int __x, __y;
		int __width, __height;
		bool __visible;
		SkColor __gackgroundColor;

		friend class Application;
	};
}
