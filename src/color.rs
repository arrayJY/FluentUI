use skulpin::skia_safe::Color4f as SkColor4f;
use skulpin::skia_safe::colors;
use std::convert::From;
use std::str::FromStr;
use std::string::String;
use serde::{Serialize, Deserialize};

#[derive(Debug, Serialize, Deserialize)]
pub enum Color {
    //Todo: More colors
    White,
    Black,
}

#[allow(dead_code)]
impl Color {
    pub fn to_str(&self) -> &'static str {
        match *self {
            Color::White => "white",
            Color::Black => "black",
        }
    }
    pub fn to_skcolor(&self) -> SkColor4f {
        match *self {
            Color::White => colors::WHITE,
            Color::Black => colors::BLACK,
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
