//! SEHasher firmware
//!
//! ATTiny44 firmware which implements a USB device emulates a keyboard
//! with an interface to automate repetitive keystrokes in computer
//! asset refurbishment.
//!

#![cfg_attr(not(test), no_std)]
#![no_main]
#![warn(clippy::all)]
#![warn(rust_2018_idioms)]
#![warn(missing_docs)]
#![warn(missing_debug_implementations)]
#![warn(missing_copy_implementations)]
#![warn(trivial_casts)]
#![warn(unused_must_use)]
#![warn(unused_unsafe)]

use attiny_hal::{
    clock::MHz20,
    delay::Delay,
    port::{mode::Output, Pin, PinOps},
    prelude::*,
};
use panic_halt as _;

#[attiny_hal::entry]
fn start() -> ! {
    let dp = attiny_hal::Peripherals::take().expect("Unable to get peripherals.");
    let pins = attiny_hal::pins!(dp);

    let mut led = pins.pb0.into_output();

    loop {
        blink(&mut led);
    }
}

fn blink<P>(led: &mut Pin<Output, P>)
where
    P: PinOps,
{
    led.toggle();
    Delay::<MHz20>::new().delay_ms(200u16);
}
