use skulpin::app::AppBuilder;
use skulpin::app::AppDrawArgs;
use skulpin::app::AppError;
use skulpin::app::AppHandler;
use skulpin::app::AppUpdateArgs;
use skulpin::skia_safe::Color;
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
                background_color: Color::from_argb(255, 255, 255, 255),
            },
        }
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
        canvas.clear(self.background_color);
    }
    fn fatal_error(&mut self, error: &AppError) {
        println!("{}", error);
    }
}
