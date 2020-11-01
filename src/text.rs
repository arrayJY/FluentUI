use serde::de::{self, Visitor};
use skulpin::skia_safe::Font as SkFont;
use skulpin::skia_safe::FontStyle;
use skulpin::skia_safe::TextBlob;
use skulpin::skia_safe::Typeface;
use std::fmt::{self};
use typetag::serde::{Deserialize, Deserializer, Serialize, Serializer};
pub struct Text {
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

struct TextVisitor;

impl<'de> Visitor<'de> for TextVisitor {
    type Value = Text;
    fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
        formatter.write_str("a string")
    }
    fn visit_str<E>(self, value: &str) -> Result<Self::Value, E>
    where
        E: de::Error,
    {
        Ok(Text::new(value))
    }
    fn visit_string<E>(self, value: String) -> Result<Self::Value, E>
    where
        E: de::Error,
    {
        Ok(Text::new(&value[..]))
    }
}

impl<'de> Deserialize<'de> for Text {
    fn deserialize<D>(deserializer: D) -> Result<Text, D::Error>
    where
        D: Deserializer<'de>,
    {
        deserializer.deserialize_str(TextVisitor)
    }
}