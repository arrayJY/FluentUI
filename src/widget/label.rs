use crate::color::Color;
use crate::text::Text;
use crate::widget::Widget;
use skulpin::skia_safe::Canvas;
use skulpin::skia_safe::Paint;
use typetag::serde::{Deserialize, Deserializer, Serialize};

#[allow(dead_code)]
#[derive(Serialize, Deserialize) ]
pub struct Label {
    #[serde(default = "default_position")]
    x: i32,
    #[serde(default = "default_position")]
    y: i32,
    #[serde(default = "default_text_color")]
    color: Color,
    #[serde(default = "default_text")]
    text: Text,
}

fn default_position() -> i32 {
    0
}

fn default_text_color() -> Color {
    Color::Black
}
fn default_text() -> Text {
    Text::new("Text")
}

#[typetag::serde]
impl Widget for Label {
    fn width(&self) -> f32 {
        self.text.width()
    }
    fn height(&self) -> f32 {
        self.text.height()
    }
    fn x(&self) -> i32 {
        self.x
    }
    fn y(&self) -> i32 {
        self.y
    }
    fn draw(&mut self, canvas: &mut Canvas) {
        let painter = Paint::new(self.color.to_skcolor(), None);
        //draw_text_blob() origin from bottom-left
        canvas.draw_text_blob(
            self.text.text_blob(),
            (self.x, self.y + self.text.height() as i32),
            &painter,
        );
    }
}