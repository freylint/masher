use core::marker::{PhantomData, PhantomPinned};

use atmega_hal::{spi::SerialClockRate, usart::Baudrate, Peripherals, Pins, Usart};

/// Initialization state
pub struct Init;

/// Initial Configuration state
pub struct Config;

pub struct Pipeline<S> {
    state: PhantomData<S>,
    dp: atmega_hal::Peripherals,
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
            serial: Usart::new(self.dp.USART0, pin!(), pin!(), Baudrate::B9600).ok(),
        }
    }
}
