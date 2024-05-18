#ifndef USBHID_H_UTILS_5182024
#define USBHID_H_UTILS_5182024

static void hardwareInit();

/* The following function returns an index for the first key pressed. It
 * returns 0 if no key is pressed.
 */
static unsigned char keyPressed();

static void buildReport(unsigned char key);

static unsigned char
usbFunctionSetup(unsigned char data[8], unsigned char *idleRate,
                 const unsigned char *keyReport[NUM_KEYS + 1][2]);

#endif