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
use quick_xml::de::{from_str};

pub struct App {
    app: AppInner,
}

#[allow(dead_code)]
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
    pub fn layout(mut self, xml: &str) -> Self {
        let widget = from_str(xml).unwrap();
        self.app.widgets.push(widget);
        self
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

struct AppInner {
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

#[allow(dead_code)]
impl AppHandler for AppInner {
    #[allow(unused_variables)]
    fn update(&mut self, update_args: AppUpdateArgs) {}

    fn draw(&mut self, draw_args: AppDrawArgs) {
        let canvas = draw_args.canvas;
        canvas.clear(self.background_color.to_skcolor());
        for widget in self.widgets.iter_mut() {
            widget.draw(canvas);
        }
    }
    fn fatal_error(&mut self, error: &AppError) {
        println!("{}", error);
    }
}
