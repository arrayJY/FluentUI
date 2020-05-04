#pragma once
#include <string>
#include <string_view>
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
		Label(std::u8string_view = u8"", Widget* parent = nullptr);
		~Label() = default;
		void setText(std::u8string_view);

		const std::u8string_view text();

	protected:
		void draw(SkCanvas*, int offsetX, int offsetY);
		void changeEvent(Event*);

	private:
		void __resize();
		std::u8string __text;
		sk_sp<SkTextBlob> blob;

		const static std::u8string_view DEFAULT_FONT;
	};
}
