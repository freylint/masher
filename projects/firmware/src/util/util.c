#include "oddebug.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "usbdrv.h"
#include "config.h"
#include "util.h"

static void hardwareInit()
{
    uchar i, j;

    PORTB = 0xff; /* activate all pull-ups */
    DDRB = 0; /* all pins input */
    PORTC = 0xff; /* activate all pull-ups */
    DDRC = 0; /* all pins input */
    PORTD = 0xfa; /* 1111 1010 bin: activate pull-ups except on USB lines
		       */
    DDRD = 0x07; /* 0000 0111 bin: all pins input except USB (-> USB
			 reset) */
    j = 0;
    while (--j) { /* USB Reset by device only required on Watchdog Reset
		       */
        i = 0;
        while (--i)
            ; /* delay >10ms for USB reset */
    }
    DDRD = 0x02; /* 0000 0010 bin: remove USB reset condition */
    /* configure timer 0 for a rate of 12M/(1024 * 256) = 45.78 Hz (~22ms)
	 */
    TCCR0 = 5; /* timer 0 prescaler: 1024 */
}

/* The following function returns an index for the first key pressed. It
 * returns 0 if no key is pressed.
 */
static unsigned char keyPressed()
{
    uchar i, mask, x;

    x = PINB;
    mask = 1;
    for (i = 0; i < 6; i++) {
        if ((x & mask) == 0)
            return i + 1;
        mask <<= 1;
    }
    x = PINC;
    mask = 1;
    for (i = 0; i < 6; i++) {
        if ((x & mask) == 0)
            return i + 7;
        mask <<= 1;
    }
    x = PIND;
    mask = 1 << 3;
    for (i = 0; i < 5; i++) {
        if ((x & mask) == 0)
            return i + 13;
        mask <<= 1;
    }
    return 0;
}

static void buildReport(unsigned char key,
                        static const unsigned char keyReport[])
{
    /* This (not so elegant) cast saves us 10 bytes of program memory */
    *(int *)reportBuffer = pgm_read_word(keyReport[key]);
}

unsigned char usbFunctionSetup(unsigned char data[8], unsigned char *idleRate)
{
    usbRequest_t *rq = (void *)data;

    usbMsgPtr = reportBuffer;
    if ((rq->bmRequestType & USBRQ_TYPE_MASK) ==
        USBRQ_TYPE_CLASS) { /* class request type */
        if (rq->bRequest == USBRQ_HID_GET_REPORT) { /* wValue: ReportType
					       (highbyte), ReportID
					       (lowbyte) */
            /* we only have one report type, so don't look at
			 * wValue
			 */
            buildReport(keyPressed());
            return sizeof(reportBuffer);
        } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            usbMsgPtr = idleRate;
            return 1;
        } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            &idleRate = rq->wValue.bytes[1];
        }
    } else {
        /* no vendor specific requests implemented */
    }
    return 0;
}