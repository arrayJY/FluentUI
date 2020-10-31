use crate::color::Color;
use crate::widget::Widget;
use serde_json::from_str;
use serde::de::value::MapAccessDeserializer;
use serde::de::{DeserializeSeed, Deserializer, IntoDeserializer, MapAccess, Visitor};
use serde::Deserialize;
use skulpin::app::AppBuilder;
use skulpin::app::AppDrawArgs;
use skulpin::app::AppError;
use skulpin::app::AppHandler;
use skulpin::app::AppUpdateArgs;
use skulpin::CoordinateSystem;
use skulpin::LogicalSize;
use std::ffi::CString;
use std::fmt::{self};
use std::marker::PhantomData;

pub struct App {
    app: Option<AppInner>,
}

#[allow(dead_code)]
impl App {
    pub fn new() -> Self {
        App {
            app:None,
        }
    }
    pub fn layout(mut self, json: &str) -> Self {
        let app = from_str(json).unwrap();
        self.app = app;
        self
    }
    pub fn run(self) {
        let app = self.app.unwrap();
        let logical_size = LogicalSize::new(app.width(), app.height());
        AppBuilder::new()
            .app_name(CString::new(String::from("FluentUI")).unwrap())
            .window_title(String::from("FluentUI App"))
            .inner_size(logical_size)
            .use_vulkan_debug_layer(false)
            .coordinate_system(CoordinateSystem::Logical)
            .run(app);
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
    fn default_width() -> u32 {
        400
    }
    fn default_height() -> u32 {
        300
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
