use crate::text::Text;
use crate::widget::Widget;
use serde::{Deserialize, Serialize};
use skulpin::skia_safe::colors;
use skulpin::skia_safe::{Canvas, Paint, Rect};

#[derive(Deserialize, Serialize)]
pub struct Button {
    #[serde(default = "Button::default_x")]
    x: i32,
    #[serde(default = "Button::default_y")]
    y: i32,
    #[serde(default = "Button::default_text")]
    text: Text,
}

impl Button {
    fn default_x() -> i32 {
        0
    }
    fn default_y() -> i32 {
        0
    }
    fn default_text() -> Text {
        Text::new("Button")
    }
}

#[typetag::serde]
impl Widget for Button {
    fn width(&self) -> f32 {
        self.text.text_blob().bounds().width() + 10.0
    }
    fn height(&self) -> f32 {
        self.text.text_blob().bounds().height() + 10.0
    }
    fn x(&self) -> i32 {
        self.x
    }
    fn y(&self) -> i32 {
        self.y
    }
    fn draw(&mut self, canvas: &mut Canvas) {
        let rect_paint = Paint::new(colors::LIGHT_GREY, None);
        let text_paint = Paint::new(colors::BLACK, None);
        let rect = Rect::from_xywh(self.x as f32, self.y as f32, self.width(), self.height());
        canvas.draw_round_rect(rect, 2.0, 2.0, &rect_paint);
        canvas.draw_text_blob(self.text.text_blob(), (self.x as f32 + 10.0, self.y as f32 + self.text.height() + 2.0), &text_paint);

    }
}
