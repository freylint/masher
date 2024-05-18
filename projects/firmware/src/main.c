/* Name: main.c
 * Project: HID-Test
 * Author: Christian Starkjohann
 * Creation Date: 2006-02-02
 * Tabsize: 4
 * Copyright: (c) 2006 by OBJECTIVE DEVELOPMENT Software GmbH
 * License: GNU GPL v2 (see License.txt) or proprietary
 * (CommercialLicense.txt) This Revision: $Id$
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>

#include "oddebug.h"
#include "usbdrv.h"
#include "util/config.h"
#include "util/util.h"

/* ----------------------- hardware I/O abstraction ------------------------
 */

/* pin assignments:
PB0	Key 1
PB1	Key 2
PB2	Key 3
PB3	Key 4
PB4	Key 5
PB5 Key 6

PC0	Key 7
PC1	Key 8
PC2	Key 9
PC3	Key 10
PC4	Key 11
PC5	Key 12

PD0	USB-
PD1	debug tx
PD2	USB+ (int0)
PD3	Key 13
PD4	Key 14
PD5	Key 15
PD6	Key 16
PD7	Key 17
*/

/* -------------------------------------------------------------------------
 */
/* ----------------------------- USB interface -----------------------------
 */
/* -------------------------------------------------------------------------
 */

static unsigned char reportBuffer[2]; /* buffer for HID reports */
static unsigned char idleRate; /* in 4 ms units */

static const unsigned char keyReport[NUM_KEYS + 1][2] PROGMEM = {
    /* none */ { 0, 0 }, /* no key pressed */
    /*  1 */ { MOD_SHIFT_LEFT, KEY_A },
    /*  2 */ { MOD_SHIFT_LEFT, KEY_B },
    /*  3 */ { MOD_SHIFT_LEFT, KEY_C },
    /*  4 */ { MOD_SHIFT_LEFT, KEY_D },
    /*  5 */ { MOD_SHIFT_LEFT, KEY_E },
    /*  6 */ { MOD_SHIFT_LEFT, KEY_F },
    /*  7 */ { MOD_SHIFT_LEFT, KEY_G },
    /*  8 */ { MOD_SHIFT_LEFT, KEY_H },
    /*  9 */ { MOD_SHIFT_LEFT, KEY_I },
    /* 10 */ { MOD_SHIFT_LEFT, KEY_J },
    /* 11 */ { MOD_SHIFT_LEFT, KEY_K },
    /* 12 */ { MOD_SHIFT_LEFT, KEY_L },
    /* 13 */ { MOD_SHIFT_LEFT, KEY_M },
    /* 14 */ { MOD_SHIFT_LEFT, KEY_N },
    /* 15 */ { MOD_SHIFT_LEFT, KEY_O },
    /* 16 */ { MOD_SHIFT_LEFT, KEY_P },
    /* 17 */ { MOD_SHIFT_LEFT, KEY_Q },
};

/* -------------------------------------------------------------------------
 */

int main(void)
{
    uchar key, lastKey = 0, keyDidChange = 0;
    uchar idleCounter = 0;

    wdt_enable(WDTO_2S);
    hardwareInit();
    odDebugInit();
    usbInit();
    sei();
    DBG1(0x00, 0, 0);
    for (;;) { /* main event loop */
        wdt_reset();
        usbPoll();
        key = keyPressed();
        if (lastKey != key) {
            lastKey = key;
            keyDidChange = 1;
        }
        if (TIFR & (1 << TOV0)) { /* 22 ms timer */
            TIFR = 1 << TOV0;
            if (idleRate != 0) {
                if (idleCounter > 4) {
                    idleCounter -= 5; /* 22 ms in units of
							     4 ms */
                } else {
                    idleCounter = idleRate;
                    keyDidChange = 1;
                }
            }
        }
        if (keyDidChange && usbInterruptIsReady()) {
            keyDidChange = 0;
            /* use last key and not current key status in order to
			   avoid lost changes in key status. */
            buildReport(lastKey);
            usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
        }
    }
    return 0;
}

/* -------------------------------------------------------------------------
 */
