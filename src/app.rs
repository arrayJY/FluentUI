use crate::color::Color;
use crate::widget::Widget;
use skulpin::app::AppBuilder;
use skulpin::app::AppDrawArgs;
use skulpin::app::AppError;
use skulpin::app::AppHandler;
use skulpin::app::AppUpdateArgs;
use skulpin::CoordinateSystem;
use skulpin::LogicalSize;
use std::ffi::CString;

pub struct App {
    app: AppInner,
}

impl App {
    pub fn new(width: u32, height: u32) -> Self {
        App {
            app: AppInner {
                width: width,
                height: height,
                background_color: Color::White,
                widgets: Vec::new(),
            },
        }
    }
    pub fn push_widget(&mut self, widget: Box<dyn Widget>)
    {
        self.app.widgets.push(widget);
    }
    pub fn run(self) {
        let logical_size = LogicalSize::new(self.app.width(), self.app.height());
        AppBuilder::new()
            .app_name(CString::new(String::from("FluentUI")).unwrap())
            .window_title(String::from("FluentUI App"))
            .inner_size(logical_size)
            .use_vulkan_debug_layer(false)
            .coordinate_system(CoordinateSystem::Logical)
            .run(self.app);
    }
}

struct AppInner{
    width: u32,
    height: u32,
    background_color: Color,
    widgets: Vec<Box<dyn Widget>>,
}

impl AppInner {
    fn width(&self) -> u32 {
        self.width
    }
    fn height(&self) -> u32 {
        self.height
    }
}

impl AppHandler for AppInner {
    fn update(&mut self, update_args: AppUpdateArgs) {}

    fn draw(&mut self, draw_args: AppDrawArgs) {
        let canvas = draw_args.canvas;
        canvas.clear(self.background_color.to_skcolor());
        for widget in self.widgets.iter_mut(){
            widget.draw(canvas);
        }
    }
    fn fatal_error(&mut self, error: &AppError) {
        println!("{}", error);
    }
}
