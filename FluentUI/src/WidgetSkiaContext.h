#pragma once
#include <include/gpu/GrContext.h>
#include <include/core/SkSurface.h>

namespace Fluentui
{
	class WidgetSkiaContext
	{
	public:
		WidgetSkiaContext(int width, int height);
		~WidgetSkiaContext() = default;
		SkCanvas* getCanvas();
		void flush();

	private:
		sk_sp<GrContext> context;
		sk_sp<SkSurface> surface;
		int width, height;
	};
}
