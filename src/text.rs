use skulpin::skia_safe::Font as SkFont;
use skulpin::skia_safe::FontStyle;
use skulpin::skia_safe::TextBlob;
use skulpin::skia_safe::Typeface;
use typetag::serde::{Serialize, Serializer};
pub struct Text {
    sk_font: SkFont,
    text: String,
    text_blob: TextBlob,
}

impl Text {
    pub fn new(text: &str) -> Self {
        const DEFAULT_FONT_SIZE: f32 = 12.0;
        const DEFAULT_FONT_FAMILY: &str = "微软雅黑";

        let font = SkFont::new(
            Typeface::new(DEFAULT_FONT_FAMILY, FontStyle::normal()).unwrap(),
            DEFAULT_FONT_SIZE,
        );
        Text {
            text: String::from(text),
            text_blob: TextBlob::new(text, &font).unwrap(),
            sk_font: font,
        }
    }
    pub fn width(&self) -> f32 {
        self.text_blob.bounds().width()
    }
    pub fn height(&self) -> f32 {
        self.text_blob.bounds().height()
    }

    pub fn text_blob(&self) -> &TextBlob {
        &self.text_blob
    }

    pub fn text(&self) -> &str {
        &self.text[..]
    }
}
 
impl Serialize for Text {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        serializer.serialize_str(self.text())
    }
}