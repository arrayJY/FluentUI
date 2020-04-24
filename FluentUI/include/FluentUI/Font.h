#pragma once
#include <include/core/SkFont.h>
#include <include/core/SkFontMgr.h>

namespace Fluentui
{
	class Font
	{
	public:
		Font(const char* fontFamily = nullptr, size_t size = DEFAULT_SIZE);
		SkFont& skFont();
		void setFont(const char* fontFamily = nullptr, size_t size = DEFAULT_SIZE);
		void setSize(size_t size = DEFAULT_SIZE);

		static const size_t DEFAULT_SIZE = 13;

	private:
		sk_sp<SkFontMgr> fontManager;
		sk_sp<SkTypeface> typeface;
		SkFontStyle fontStyle;
		SkFont font;
	};
}
