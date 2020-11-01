use skulpin::skia_safe::Canvas;
pub mod label;
pub mod textfield;

#[typetag::serde]
pub trait Widget {
    fn width(&self) -> f32;
    fn height(&self) -> f32;
    fn x(&self) -> i32;
    fn y(&self) -> i32;
    fn draw(&mut self, canvas: &mut Canvas);
}
