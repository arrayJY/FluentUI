use crate::color::Color;
use crate::widget::Widget;
use serde::de::value::MapAccessDeserializer;
use serde::de::{DeserializeSeed, Deserializer, IntoDeserializer, MapAccess, Visitor};
use serde::Deserialize;
use serde_json::from_str;
use skulpin::skia_safe::Canvas;
use skulpin::winit;
use skulpin::CoordinateSystem;
use std::fmt::{self};
use std::marker::PhantomData;

pub struct App {
    app: Option<AppInner>,
}

#[allow(dead_code)]
impl App {
    pub fn new() -> Self {
        App { app: None }
    }
    pub fn layout(mut self, json: &str) -> Self {
        let app = from_str(json).unwrap();
        self.app = app;
        self
    }
    pub fn run(self) {
        let event_loop = winit::event_loop::EventLoop::<()>::with_user_event();
        let mut app = self.app.unwrap();
        let logical_size = winit::dpi::LogicalSize::new(app.width(), app.height());
        let winit_window = winit::window::WindowBuilder::new()
            .with_title(app.title())
            .with_inner_size(logical_size)
            .build(&event_loop)
            .expect("Failed to create window");

        let window = skulpin::WinitWindow::new(&winit_window);
        let renderer = skulpin::RendererBuilder::new()
            .use_vulkan_debug_layer(false)
            .coordinate_system(CoordinateSystem::Logical)
            .build(&window);

        if let Err(e) = renderer {
            println!("Error during renderer construction: {:?}", e);
            return;
        }

        let mut renderer = renderer.unwrap();
        event_loop.run(move |event, _window_target, control_flow| {
            let window = skulpin::WinitWindow::new(&winit_window);

            match event {
                winit::event::Event::WindowEvent {
                    event: winit::event::WindowEvent::CloseRequested,
                    ..
                } => *control_flow = winit::event_loop::ControlFlow::Exit,
                winit::event::Event::MainEventsCleared => {
                    // Queue a RedrawRequested event.
                    winit_window.request_redraw();
                }

                //
                // Redraw
                //
                winit::event::Event::RedrawRequested(_window_id) => {
                    if let Err(e) = renderer.draw(&window, |canvas, _coordinate_system_helper| {
                        app.draw(canvas)
                    }) {
                        println!("Error during draw: {:?}", e);
                        *control_flow = winit::event_loop::ControlFlow::Exit
                    }
                }

                //
                // Ignore all other events
                //
                _ => {}
            }
        });
    }
}

#[derive(Deserialize)]
struct AppInner {
    #[serde(default = "AppInner::default_width")]
    width: u32,
    #[serde(default = "AppInner::default_height")]
    height: u32,
    #[serde(default = "AppInner::default_color")]
    background_color: Color,
    #[serde(default = "AppInner::default_title")]
    title: String,
    #[serde(deserialize_with = "AppInner::from_typetag_objects")]
    widgets: Vec<Box<dyn Widget>>,
}

impl AppInner {
    fn width(&self) -> u32 {
        self.width
    }
    fn height(&self) -> u32 {
        self.height
    }
    fn title(&self) -> &str {
        &self.title[..]
    }
    fn default_width() -> u32 {
        400
    }
    fn default_height() -> u32 {
        300
    }
    fn default_title() -> String {
        String::from("FluentUI App")
    }
    fn default_color() -> Color {
        Color::White
    }
    fn from_typetag_objects<'de, D, T>(deserializer: D) -> Result<Vec<T>, D::Error>
    where
        D: Deserializer<'de>,
        T: Deserialize<'de>,
    {
        struct TypetagObjects<T> {
            _type: PhantomData<T>,
        }

        impl<'de, T> Visitor<'de> for TypetagObjects<T>
        where
            T: Deserialize<'de>,
        {
            type Value = Vec<T>;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                formatter.write_str("zero or more typename-to-value pairs")
            }

            fn visit_map<M>(self, mut map: M) -> Result<Self::Value, M::Error>
            where
                M: MapAccess<'de>,
            {
                let mut vec = Vec::new();
                while let Some(key) = map.next_key::<String>()? {
                    let de = MapAccessDeserializer::new(Entry {
                        key: Some(key.into_deserializer()),
                        value: &mut map,
                    });
                    vec.push(T::deserialize(de)?);
                }
                Ok(vec)
            }
        }

        struct Entry<K, V> {
            key: Option<K>,
            value: V,
        }

        impl<'de, K, V> MapAccess<'de> for Entry<K, V>
        where
            K: Deserializer<'de, Error = V::Error>,
            V: MapAccess<'de>,
        {
            type Error = V::Error;

            fn next_key_seed<S>(&mut self, seed: S) -> Result<Option<S::Value>, Self::Error>
            where
                S: DeserializeSeed<'de>,
            {
                self.key.take().map(|key| seed.deserialize(key)).transpose()
            }

            fn next_value_seed<S>(&mut self, seed: S) -> Result<S::Value, Self::Error>
            where
                S: DeserializeSeed<'de>,
            {
                self.value.next_value_seed(seed)
            }
        }

        deserializer.deserialize_map(TypetagObjects { _type: PhantomData })
    }
    fn draw(&mut self, canvas: &mut Canvas) {
        canvas.clear(self.background_color.to_skcolor());
        for widget in self.widgets.iter_mut() {
            widget.draw(canvas);
        }
    }
}