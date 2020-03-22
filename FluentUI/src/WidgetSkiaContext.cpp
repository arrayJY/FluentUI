#include "WidgetSkiaContext.h"
#include <GLFW/glfw3.h>
#include <include/core/SkColor.h>
#include <include/core/SkColorSpace.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkSurface.h>
#include <include/gpu/GrContext.h>
#include <include/gpu/GrBackendSurface.h>
#include <include/gpu/gl/GrGLInterface.h>

Fluentui::WidgetSkiaContext::WidgetSkiaContext(int width, int height)
	: width(width), height(height),
	  context(nullptr), surface(nullptr)
{
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
}

SkCanvas* Fluentui::WidgetSkiaContext::getCanvas()
{
	return surface->getCanvas();
}

void Fluentui::WidgetSkiaContext::flush()
{
	context->flush();
}