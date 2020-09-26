use skulpin::skia_safe::Color as SkColor;
use std::convert::From;
use std::str::FromStr;
use std::string::String;

#[derive(Debug)]
pub enum Color {
    //Todo: More colors
    White,
    Black,
}

impl Color {
    pub fn to_str(&self) -> &'static str {
        match *self {
            Color::White => "white",
            Color::Black => "black",
        }
    }
    pub fn to_skcolor(&self) -> SkColor {
        match *self {
            Color::White => SkColor::WHITE,
            Color::Black => SkColor::BLACK,
        }
    }
}

impl<'a> From<&'a str> for Color {
    fn from(src: &str) -> Self {
        src.parse().unwrap_or(Color::Black)
    }
}

impl From<String> for Color {
    fn from(src: String) -> Self {
        src.parse().unwrap_or(Color::Black)
    }
}

impl FromStr for Color {
    type Err = ();
    fn from_str(src: &str) -> Result<Self, Self::Err> {
        let src = src.to_lowercase();
        match src.as_ref() {
            "black" => Ok(Color::Black),
            "white" => Ok(Color::White),
            _ => Err(()),
        }
    }
}
