use crate::widget::Widget;
use serde::{Deserialize, Serialize};
use skulpin::skia_safe::colors;
use skulpin::skia_safe::{Canvas, Paint, Rect};

#[derive(Deserialize, Serialize)]
pub struct TextField {
    #[serde(default="TextField::default_width")]
    width: f32,
    #[serde(default="TextField::default_height")]
    height: f32,
    #[serde(default="TextField::default_x")]
    x: i32,
    #[serde(default="TextField::default_y")]
    y: i32,
}

impl TextField{
    //Default value
    fn default_width() -> f32 {
        100.0
    }
    fn default_height() -> f32 {
        20.0
    }
    fn default_x() -> i32 {
        0
    }
    fn default_y() -> i32 {
        0
    }
}

#[typetag::serde]
impl Widget for TextField {
    fn width(&self) -> f32 {
        self.width
    }
    fn height(&self) -> f32 {
        self.height
    }
    fn x(&self) -> i32 {
        self.x
    }
    fn y(&self) -> i32 {
        self.y
    }
    fn draw(&mut self, canvas: &mut Canvas) {
        let mut painter = Paint::new(colors::GREY, None);
        painter.set_stroke(true).set_stroke_width(1.5);
        let rect = Rect::from_xywh(self.x as f32, self.y as f32, self.width, self.height);
        canvas.draw_rect(rect, &painter);
    }

}
