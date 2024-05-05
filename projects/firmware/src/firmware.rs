//! SEHasher firmware
//!
//! ATTiny44 firmware which implements a USB device emulates a keyboard
//! with an interface to automate repetitive keystrokes in computer
//! asset refurbishment.
//!

#![no_std]
#![no_main]
#![warn(clippy::all)]
#![warn(rust_2018_idioms)]
#![warn(missing_docs)]
#![warn(missing_debug_implementations)]
#![warn(missing_copy_implementations)]
#![warn(trivial_casts)]
#![warn(unused_must_use)]
#![warn(unused_unsafe)]

use atmega_hal::{pins, usart::UsartWriter, Peripherals};
use core::marker::PhantomData;
use panic_halt as _;

mod pipeline;

/// Operation Mode Selector
///
/// This models external device state from
/// the input switch.
enum ModeSelect {
    F1,
    F2,
    F10,
    F12,
    /// Mashes ESC and Space
    BLNC,
    NOKEY,
}

#[atmega_hal::entry]
fn start() -> ! {
    let pipeline = pipeline::Pipeline::new(Peripherals::take().unwrap());

    loop {}
}
