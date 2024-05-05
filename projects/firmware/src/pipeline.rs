use core::marker::PhantomData;

use attiny_hal::Peripherals;

/// Initialization state
pub struct Init;

/// Initial Configuration state
pub struct Config;

pub struct Pipeline<S> {
    state: PhantomData<S>,
    dp: attiny_hal::Peripherals,
    serial: Option<()>,
}

impl Pipeline<Init> {
    pub fn new(dp: Peripherals) -> Pipeline<Config> {
        Pipeline::<Config> {
            state: PhantomData,
            serial: None,
            dp,
        }
    }
}

impl Pipeline<Config> {
    pub fn configure(self) -> Pipeline<Init> {
        Pipeline {
            state: PhantomData,
            dp: self.dp,
            serial: None,
        }
    }
}
