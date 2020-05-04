#pragma once
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>

namespace Fluentui
{
	class Font
	{
	public:
		Font();
		Font(std::u8string_view fontFamily, size_t size = DEFAULT_SIZE);
		const SkFont& skFont() const;
		void setFont(std::u8string_view fontFamily = u8"", size_t size = DEFAULT_SIZE);
		void setSize(size_t size = DEFAULT_SIZE);

		static const size_t DEFAULT_SIZE = 12;

	private:
		sk_sp<SkFontMgr> __fontManager;
		sk_sp<SkTypeface> __typeface;
		SkFontStyle __fontStyle;
		SkFont __font;
		size_t __size;
		static const std::u8string_view DEFAULT_FONT_FAMILY;
	};
}
