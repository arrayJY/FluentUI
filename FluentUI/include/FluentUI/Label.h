#pragma once
#include <string>
#include <FluentUI/Widget.h>
#include <FluentUI/Font.h>
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>
#include <include/core/SkTextBlob.h>

namespace Fluentui
{
	class Label : public Widget
	{
	public:
		Label(const char*, Widget* parent = nullptr);
		~Label() = default;
		void setFont(const char*);
		void setText(const char*);
		void setSize(size_t size);

		const std::string& text();

	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);

	private:
		void resize();
		Font font;
		std::string __text;
		size_t size;
		sk_sp<SkTextBlob> blob;
	};
}
