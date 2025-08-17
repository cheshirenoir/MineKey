#include <HID_Keyboard.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Rotary.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define MOUSE_SCROLL_AMOUNT 3 //How many lines to scroll the virtual middle mouse on th rotary encoder.

// constants won't change. They're used here to set pin numbers:
const int rowPin1 = 9;        // For row and column scan, row 1 pin
const int rowPin2 = 8;        // For row and column scan, row 2 pin
const int rowPin3 = 7;        // For row and column scan, row 3 pin
const int rowPin4 = 6;        // For row and column scan, row 4 pin

const int colPin1 = 13;       // For row and column scan, column 1 pin
const int colPin2 = 12;       // For row and column scan, column 2 pin
const int colPin3 = 11;       // For row and column scan, column 3 pin
const int colPin4 = 10;       // For row and column scan, column 4 pin

const int buttonPinRL = 18;   // the number of the pushbutton pin
const int buttonPinRR = 21;   // the number of the pushbutton pin
const int buttonPin17 = 3;    // the number of the pushbutton pin
const int buttonPin18 = 2;    // the number of the pushbutton pin

//MICHAEL: Comment out the two lines above and uncmment the two lines below.
//const int buttonPin17 = 1;    // the number of the pushbutton pin
//const int buttonPin18 = 0;    // the number of the pushbutton pin

// Pins for rotary encoder
const int PIN_ROT_A = 16;
const int PIN_ROT_B = 17;
const int PIN_ROT_C = 19;
const int PIN_ROT_D = 20;

//Bitmaps
static const uint8_t image_data_META[512] = {
    0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xe0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x40, 0x1f, 0xff, 0xff, 
    0xff, 0xff, 0xe0, 0xfc, 0x0f, 0x1f, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 
    0xff, 0xef, 0x00, 0xfc, 0x7f, 0x8f, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 
    0xf8, 0x62, 0x02, 0xfc, 0x3f, 0xc7, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xff, 0xff, 
    0xf0, 0x08, 0xc0, 0xfe, 0x7f, 0xe7, 0x1f, 0xff, 0x07, 0xff, 0x3f, 0xfc, 0x0f, 0xe7, 0xff, 0xff, 
    0xf1, 0x88, 0xe1, 0xfe, 0x7f, 0xe2, 0x3f, 0xe0, 0x00, 0x00, 0x0b, 0xe0, 0x07, 0xe7, 0xff, 0xff, 
    0xf0, 0x03, 0x33, 0xfc, 0x7f, 0xf0, 0x7f, 0xe0, 0x00, 0x00, 0x13, 0xe0, 0xe7, 0xf3, 0xff, 0xff, 
    0xf0, 0x47, 0x9f, 0xfc, 0x7f, 0xf8, 0xff, 0xf3, 0xff, 0xff, 0xfb, 0xe7, 0xe7, 0xf3, 0xff, 0xff, 
    0xf7, 0xc4, 0x00, 0x7c, 0x7f, 0xf8, 0xfd, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0xef, 0xf1, 0xff, 0xff, 
    0xe7, 0xc0, 0x0f, 0x7e, 0x7f, 0xfc, 0xf8, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0xef, 0xf9, 0xff, 0xff, 
    0xef, 0x01, 0x8f, 0x8c, 0x79, 0xff, 0xf0, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0xee, 0x78, 0xff, 0xff, 
    0xee, 0x00, 0x07, 0x04, 0xf8, 0xff, 0xe0, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0xce, 0x3c, 0xff, 0xff, 
    0xe4, 0x80, 0x03, 0x24, 0xf8, 0x7f, 0xc0, 0xf0, 0x7f, 0xff, 0xf9, 0xe7, 0xce, 0x3c, 0x7f, 0xff, 
    0xf1, 0x80, 0x03, 0x24, 0xf9, 0x3f, 0xc8, 0xe0, 0x3f, 0xff, 0xf9, 0xe7, 0xce, 0x9e, 0x7f, 0xff, 
    0xe3, 0x80, 0x03, 0x04, 0xf9, 0x0f, 0x08, 0xff, 0x1f, 0xff, 0xf9, 0xe7, 0xcc, 0x9e, 0x3f, 0xff, 
    0xe0, 0x80, 0x03, 0x9c, 0xf9, 0xc7, 0x18, 0xff, 0x9f, 0xff, 0xf9, 0xe7, 0x9c, 0x1e, 0x3f, 0xff, 
    0xf0, 0x0c, 0x63, 0xfc, 0xf9, 0xe2, 0x38, 0xfe, 0x1f, 0xff, 0xf9, 0xe7, 0x9c, 0x1f, 0x3f, 0xff, 
    0xfc, 0x00, 0x01, 0xfc, 0xf9, 0xf0, 0x7c, 0xf0, 0x3f, 0xff, 0xf9, 0xe7, 0x9f, 0xff, 0x1f, 0xff, 
    0xfe, 0x01, 0x81, 0xfc, 0xf9, 0xf8, 0xfc, 0xf1, 0xbf, 0xff, 0xf9, 0xe7, 0xbf, 0xff, 0x9f, 0xff, 
    0xf8, 0x00, 0xcb, 0xfc, 0xf9, 0xfc, 0xfc, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0x3f, 0xcf, 0x9f, 0xff, 
    0xf8, 0x2f, 0x9b, 0xfc, 0xf9, 0xff, 0xfc, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0x3c, 0x07, 0x8f, 0xff, 
    0xf1, 0x2e, 0x10, 0xfc, 0xf9, 0xff, 0xfc, 0xf3, 0xff, 0xff, 0xf9, 0xe7, 0x38, 0x67, 0xcf, 0xff, 
    0xf1, 0x24, 0x00, 0xfc, 0xf9, 0xff, 0xfc, 0xf2, 0x00, 0x01, 0xf9, 0xe6, 0x79, 0xf3, 0xc7, 0xff, 
    0xf0, 0x70, 0x46, 0x7c, 0xf9, 0xff, 0xfc, 0xf0, 0x00, 0x01, 0xf9, 0xe6, 0x79, 0xf1, 0xc7, 0xff, 
    0xf9, 0x01, 0xc2, 0xfc, 0xf9, 0xff, 0xfc, 0xf0, 0x7f, 0xf9, 0xf9, 0xe6, 0x7b, 0xf9, 0xe3, 0xff, 
    0xff, 0xc7, 0xc1, 0xfc, 0xf9, 0xff, 0xfc, 0xff, 0xff, 0xf9, 0xf9, 0xe6, 0x73, 0xfc, 0xf3, 0xff, 
    0xff, 0xff, 0xe3, 0xfc, 0xf9, 0xff, 0xfc, 0xff, 0xff, 0xf9, 0xf1, 0xe6, 0x73, 0xfc, 0x71, 0xff, 
    0xff, 0xff, 0xff, 0xfc, 0xf9, 0xff, 0xfc, 0xff, 0xff, 0xf9, 0xf3, 0xec, 0xf3, 0xfe, 0x39, 0xff, 
    0xff, 0xff, 0xff, 0xf8, 0xf9, 0xff, 0xfc, 0x1f, 0xe0, 0x01, 0xf3, 0x8c, 0xe7, 0xff, 0x38, 0xff, 
    0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xf0, 0x0c, 0x07, 0xff, 0x00, 0xff, 
    0xff, 0xff, 0xff, 0xf8, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xf0, 0x04, 0x07, 0xff, 0x03, 0xff
};

static const uint8_t image_data_SUPER[512] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xf3, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xfc, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xc7, 0x9f, 0xff, 0xff, 0xff, 
    0xf8, 0x0f, 0xfe, 0x43, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0x00, 0x03, 0xc0, 0x0f, 0xff, 0xff, 0xff, 
    0xf0, 0x3f, 0xff, 0xe3, 0xff, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf8, 0x4c, 0xcf, 0xff, 0xff, 0xff, 
    0xe0, 0x7e, 0x1f, 0xe0, 0x1f, 0x3e, 0x00, 0x00, 0xff, 0x9c, 0x02, 0x0f, 0x9f, 0xff, 0xff, 0xff, 
    0xc0, 0xf8, 0x07, 0xf0, 0x1f, 0x7e, 0x7f, 0xfe, 0x7f, 0x1c, 0xe1, 0xcf, 0x9f, 0xff, 0xff, 0xff, 
    0xc0, 0xf0, 0x01, 0xf0, 0xdf, 0x7e, 0x7f, 0xff, 0x3f, 0x5d, 0xfc, 0xc7, 0x9f, 0xff, 0xff, 0xff, 
    0xc0, 0xf0, 0x00, 0x78, 0x5e, 0x7e, 0xc0, 0x7f, 0xa6, 0x5d, 0xfe, 0xe7, 0x9f, 0xff, 0xff, 0xff, 
    0xe0, 0xf8, 0x00, 0x00, 0x5e, 0x7e, 0xcf, 0x3f, 0x00, 0x5d, 0xf8, 0xe7, 0xbf, 0xff, 0xff, 0xff, 
    0xf0, 0x7f, 0x00, 0x00, 0x9e, 0xfe, 0xdf, 0x7f, 0x1f, 0xdd, 0xe1, 0xc7, 0x3f, 0xff, 0xff, 0xff, 
    0xf8, 0x3f, 0xff, 0xc0, 0x9c, 0xfc, 0xce, 0x7f, 0x43, 0xdc, 0x0f, 0x87, 0x3f, 0xff, 0xff, 0xff, 
    0xf8, 0x1f, 0xff, 0xc1, 0x9c, 0xfc, 0xc0, 0xfe, 0x73, 0xdf, 0x3c, 0x27, 0x3f, 0xff, 0xff, 0xff, 
    0xfc, 0x00, 0xff, 0xc3, 0x9c, 0xfc, 0xff, 0xfc, 0xf3, 0xdf, 0xf8, 0xe6, 0x7f, 0xff, 0xff, 0xff, 
    0xfe, 0x00, 0x0f, 0xc3, 0x99, 0xfd, 0xff, 0xf9, 0xf3, 0x9f, 0xe3, 0xf6, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0x00, 0x0f, 0x87, 0x93, 0xfd, 0xff, 0xf3, 0x83, 0x98, 0xef, 0xe6, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0x84, 0x3f, 0x07, 0xc3, 0xf9, 0xff, 0x87, 0x87, 0x98, 0x67, 0xe0, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0x87, 0xfe, 0x07, 0xff, 0xf9, 0x80, 0x37, 0x3f, 0x19, 0x27, 0xfc, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xc3, 0xf8, 0x1b, 0xff, 0xfb, 0x81, 0xe7, 0x20, 0x19, 0xb3, 0xe1, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xf3, 0xe0, 0x3b, 0xff, 0xfb, 0x9f, 0xef, 0x02, 0x19, 0x99, 0xc8, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0xf1, 0x00, 0x3b, 0xff, 0xf3, 0x9f, 0xef, 0xfe, 0x39, 0xdc, 0xce, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0xf9, 0x00, 0x7b, 0xff, 0xf7, 0x9f, 0xef, 0xfe, 0x39, 0xcc, 0xde, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0xfc, 0x00, 0xfb, 0xff, 0xc7, 0x9f, 0xcf, 0xfe, 0x01, 0xe0, 0x40, 0x7f, 0xff, 0xff, 0xff, 
    0xff, 0xfe, 0x01, 0xfd, 0xff, 0x96, 0x1f, 0xc0, 0x0e, 0x01, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x03, 0xfc, 0x7e, 0x30, 0x1f, 0xc0, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x07, 0xff, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0x87, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xcf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xdf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

static const uint8_t image_data_SNM[512] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 
    0xfe, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3f, 
    0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 
    0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xfe, 0x00, 0x3f, 0xff, 0xff, 0x00, 0x1f, 
    0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xf8, 0x00, 0x00, 0x00, 0x0f, 0x01, 0x1f, 
    0xe0, 0x0f, 0xf0, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xb1, 0xf8, 0x3f, 0x00, 0x00, 0x0f, 0x10, 0x07, 
    0xc0, 0x3f, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xb8, 0x73, 0xff, 0xff, 0xff, 0xe7, 0x00, 0x07, 
    0xc0, 0x70, 0x38, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xbc, 0x27, 0x80, 0x03, 0x80, 0x66, 0x00, 0x0f, 
    0x80, 0x60, 0x38, 0x07, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x04, 0x80, 0x01, 0x80, 0x72, 0x00, 0x1f, 
    0x00, 0x60, 0x30, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x8c, 0x9c, 0x19, 0x9e, 0x72, 0x00, 0x0f, 
    0x00, 0x60, 0x30, 0x18, 0x03, 0x00, 0x00, 0x7f, 0x91, 0x8c, 0x9f, 0xf9, 0x9e, 0x78, 0x00, 0x2f, 
    0x80, 0x78, 0x00, 0x30, 0x21, 0x00, 0x00, 0x1f, 0x90, 0xd8, 0x9f, 0xf9, 0x9c, 0xc8, 0x00, 0x0f, 
    0xc0, 0x3f, 0x00, 0x33, 0x3c, 0x7f, 0x8b, 0x8f, 0x90, 0x70, 0x9f, 0xf9, 0xbc, 0x8c, 0x80, 0x0f, 
    0xe0, 0x1f, 0x80, 0x73, 0x3e, 0x73, 0x80, 0xcf, 0x92, 0x70, 0x9f, 0xf9, 0xb9, 0x84, 0xe0, 0x1f, 
    0xe0, 0x07, 0xc0, 0x73, 0x03, 0x20, 0x04, 0xcf, 0xb3, 0x20, 0x83, 0xf9, 0xb9, 0xb4, 0x63, 0xff, 
    0xf0, 0x00, 0xc0, 0xf3, 0x21, 0x80, 0x0e, 0x49, 0x93, 0x04, 0x81, 0xf8, 0xb9, 0x02, 0x7f, 0xff, 
    0xf0, 0x00, 0xc0, 0xf3, 0x2c, 0x87, 0x60, 0x99, 0x93, 0x8c, 0xf9, 0xf8, 0x39, 0x02, 0x7f, 0xff, 
    0xf8, 0x10, 0xc1, 0xf3, 0x21, 0xc6, 0x61, 0x81, 0x93, 0xdc, 0x99, 0xf8, 0x31, 0xfe, 0x7f, 0xff, 
    0xf8, 0x11, 0xc1, 0xe3, 0x33, 0x86, 0x6e, 0x00, 0x13, 0xfc, 0x81, 0xf8, 0x33, 0xfe, 0x3f, 0xff, 
    0xfc, 0x39, 0xc0, 0xe7, 0x3c, 0x00, 0x78, 0x00, 0x13, 0xf8, 0x83, 0xf8, 0x33, 0xff, 0x3f, 0xff, 
    0xfc, 0x3f, 0x80, 0xe7, 0x20, 0x20, 0x78, 0xe0, 0x13, 0xf9, 0x9f, 0xf8, 0x27, 0x03, 0x1f, 0xff, 
    0xfe, 0x3f, 0x04, 0xe7, 0x22, 0x60, 0x7c, 0xf1, 0x93, 0xf9, 0x9f, 0xf9, 0xa6, 0x01, 0x9f, 0xff, 
    0xfe, 0x00, 0x00, 0xe6, 0x66, 0x40, 0x66, 0x71, 0x93, 0xf9, 0x91, 0xc9, 0xa6, 0x79, 0x8f, 0xff, 
    0xff, 0x00, 0x09, 0xc6, 0x64, 0x40, 0x42, 0x39, 0x93, 0xf9, 0x80, 0x09, 0xa4, 0xf8, 0x8f, 0xff, 
    0xff, 0x00, 0x08, 0x0e, 0x64, 0xce, 0x43, 0x3f, 0x93, 0xf9, 0xfe, 0x49, 0x8c, 0xfc, 0x0f, 0xff, 
    0xff, 0x80, 0x0c, 0x1e, 0x64, 0xc0, 0x41, 0x1f, 0x93, 0xf8, 0xff, 0xe8, 0x01, 0xfe, 0x0f, 0xff, 
    0xff, 0xc0, 0x2f, 0xfc, 0xe4, 0xc0, 0x49, 0x8f, 0x93, 0xfc, 0x00, 0x04, 0x01, 0xfe, 0x1f, 0xff, 
    0xff, 0xc0, 0x27, 0xf8, 0x04, 0x7e, 0x4c, 0x8f, 0x83, 0xfc, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xe0, 0x73, 0xe0, 0x0c, 0x00, 0x04, 0x0f, 0x83, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xe0, 0xf0, 0x01, 0x8e, 0x00, 0x0c, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xf8, 0xfc, 0x3f, 0xfe, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

//Mapping into an array of all 16 keys so they can be swapped out easily
//Order is SW1-SW16
//These are the raw keymappings as sent to the HID output.
char keycharmap[4][16] = {
  {0x5f,0x60,0x61,0x54,0x5c,0x5d,0x5e,0x55,0x59,0x5a,0x5b,0x56,0x62,0x63,0x58,0x57},
  {0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77},
  {0xe8,0xe9,0xea,0xeb,0xec,0xef,0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf9,0xfb},
  {0x85,0x89,0x88,0x8a,0xbc,0xbd,0xbe,0xbf,0xc0,0xc1,0xb0,0xb1,0xc2,0xce,0xd7,0xcf}
};
//Row one is Numeric Keypad 7,8,9,/,4,5,6,*,1,2,3,-,0,stop,return,+
//Row two is Additional Function keys F13,F14,F15,F16,F17,F18,F19,F20,F21,F22,F23,F24,KEY_OPEN,KEY_HELP,KEY_PROPS,KEY_FRONT
//Row three is multimedia keys KEY_MEDIA_PLAYPAUSE,KEY_MEDIA_STOPCD,KEY_MEDIA_PREVIOUSSONG,KEY_MEDIA_NEXTSONG,KEY_MEDIA_EJECTCD,KEY_MEDIA_WWW,KEY_MEDIA_BACK,KEY_MEDIA_FORWARD,KEY_MEDIA_STOP,KEY_MEDIA_FIND,KEY_MEDIA_SCROLLUP,KEY_MEDIA_SCROLLDOWN,KEY_MEDIA_EDIT,KEY_MEDIA_COFFEE,KEY_MEDIA_REFRESH,KEY_MEDIA_CALC
//Row four is all sorts of random keys. Many probably won't work. KEY_KPCOMMA,KEY_YEN,KEY_KATAKANAHIRAGANA,KEY_HENKAN,Keypad_A,Keypad_B,Keypad_C,Keypad_D,Keypad_E,Keypad_F,Keypad_00,Keypad_000,Keypad_XOR,Keypad_@,Keypad_+/-,Keypad_!


// Declare the two rotary encoders
Rotary rotaryL = Rotary(PIN_ROT_A, PIN_ROT_B);
Rotary rotaryR = Rotary(PIN_ROT_C, PIN_ROT_D);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);

// Variables will change:
int buttonState1;				      // the current reading from the input pin
int lastButtonState1 = LOW;		// the previous reading from the input pin
int buttonState2;				      // the current reading from the input pin
int lastButtonState2 = LOW;		// the previous reading from the input pin
int buttonState3;				      // the current reading from the input pin
int lastButtonState3 = LOW;		// the previous reading from the input pin
int buttonState4;				      // the current reading from the input pin
int lastButtonState4 = LOW;		// the previous reading from the input pin
int buttonState5;				      // the current reading from the input pin
int lastButtonState5 = LOW;		// the previous reading from the input pin
int buttonState6;				      // the current reading from the input pin
int lastButtonState6 = LOW;		// the previous reading from the input pin
int buttonState7;				      // the current reading from the input pin
int lastButtonState7 = LOW;		// the previous reading from the input pin
int buttonState8;				      // the current reading from the input pin
int lastButtonState8 = LOW;		// the previous reading from the input pin
int buttonState9;				      // the current reading from the input pin
int lastButtonState9 = LOW;		// the previous reading from the input pin
int buttonState10;				    // the current reading from the input pin
int lastButtonState10 = LOW;	// the previous reading from the input pin
int buttonState11;				    // the current reading from the input pin
int lastButtonState11 = LOW;	// the previous reading from the input pin
int buttonState12;			    	// the current reading from the input pin
int lastButtonState12 = LOW;	// the previous reading from the input pin
int buttonState13;				    // the current reading from the input pin
int lastButtonState13 = LOW;	// the previous reading from the input pin
int buttonState14;	    			// the current reading from the input pin
int lastButtonState14 = LOW;	// the previous reading from the input pin
int buttonState15;		    		// the current reading from the input pin
int lastButtonState15 = LOW;	// the previous reading from the input pin
int buttonState16;	    			// the current reading from the input pin
int lastButtonState16 = LOW;	// the previous reading from the input pin
int buttonStateRL;            // the current reading from the input pin
int lastButtonStateRL = LOW;  // the previous reading from the input pin
int buttonStateRR;            // the current reading from the input pin
int lastButtonStateRR = LOW;  // the previous reading from the input pin
int buttonState17;            // the current reading from the input pin
int lastButtonState17 = LOW;  // the previous reading from the input pin
int buttonState18;            // the current reading from the input pin
int lastButtonState18 = LOW;  // the previous reading from the input pin

int metasuper = 0;  // Used to record whether the META and SUPER keys are pressed. For META add 1 for SUPER add 2. This becomes the index for which keyset
int lastmetasuper = 0; // Used to determine changes in the status of the META / SUPER keys

// Counter that will be incremented or decremented by rotation.
int rotaryLcount = 0;
int rotaryRcount = 0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime4 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime5 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime6 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime7 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime8 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime9 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime10 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime11 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime12 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime13 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime14 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime15 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime16 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeRL = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTimeRR = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime17 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime18 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 30;    // the debounce time; increase if the output flickers

// Which column are we currently working on? This cycles 1-4 on a pass through the main loop
int currentCol = 1;

void setup() {
  
  // setup the I2C port
  Wire1.setSDA(26);
  Wire1.setSCL(27);
  Wire1.begin();

  // Fire up display, clear it, rotate it then push the changes.
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setRotation(2);
  display.display(); 
  
  // setup the fixed buttons
  pinMode(buttonPinRL, INPUT_PULLDOWN);
  pinMode(buttonPinRR, INPUT_PULLDOWN);
  pinMode(buttonPin17, INPUT_PULLDOWN);
  pinMode(buttonPin18, INPUT_PULLDOWN);

  // setup the rows and columns.
  pinMode(rowPin1, INPUT_PULLDOWN);
  pinMode(rowPin2, INPUT_PULLDOWN);
  pinMode(rowPin3, INPUT_PULLDOWN);
  pinMode(rowPin4, INPUT_PULLDOWN);
  pinMode(colPin1, OUTPUT);
  pinMode(colPin2, OUTPUT);
  pinMode(colPin3, OUTPUT);
  pinMode(colPin4, OUTPUT);
  
  // setup the keyboard output.
  Keyboard.begin();
  Mouse.begin();

  // set all the columns to low so nothing gets read.
  digitalWrite(colPin1, LOW);
  digitalWrite(colPin2, LOW);
  digitalWrite(colPin3, LOW);
  digitalWrite(colPin4, LOW);

  // Attach interrupts for Rotary Encoder
  pinMode(PIN_ROT_A, INPUT_PULLUP); // Enable if not using KY-040 or HW-040
  pinMode(PIN_ROT_B, INPUT_PULLUP); // as has pull up resitors on board
  pinMode(PIN_ROT_C, INPUT_PULLUP); // Enable if not using KY-040 or HW-040
  pinMode(PIN_ROT_D, INPUT_PULLUP); // as has pull up resitors on board
  attachInterrupt(digitalPinToInterrupt(PIN_ROT_A), rotateL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ROT_B), rotateL, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ROT_C), rotateR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ROT_D), rotateR, CHANGE);
}

void loop() {
  // read the state of the Rotary Left switch into a local variable:
  int reading = digitalRead(buttonPinRL);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonStateRL) {
    // reset the debouncing timer
    lastDebounceTimeRL = millis();
  }

  if ((millis() - lastDebounceTimeRL) > debounceDelay) 
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonStateRL) 
    {
      buttonStateRL = reading;

      // only output the character if the new button state is HIGH, else release the key.
      if (buttonStateRL == HIGH) 
      {
        Keyboard.press(KEY_NUM_LOCK);
      }
      else
      {
	      Keyboard.release(KEY_NUM_LOCK);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonStateRL = reading;

  // Now Rotary Right
  reading = digitalRead(buttonPinRR);

  if (reading != lastButtonStateRR) 
  {
    lastDebounceTimeRR = millis();
  }

  if ((millis() - lastDebounceTimeRR) > debounceDelay) 
  {
    if (reading != buttonStateRR) 
    {
      buttonStateRR = reading;
      if (buttonStateRR == HIGH) 
      {
        Keyboard.consumerPress(KEY_MUTE);
        Keyboard.consumerRelease();
      }
    }
  }

  lastButtonStateRR = reading;

  // Now the META key
  reading = digitalRead(buttonPin17);

  if (reading != lastButtonState17) 
  {
    lastDebounceTime17 = millis();
  }

  if ((millis() - lastDebounceTime17) > debounceDelay) 
  {
    if (reading != buttonState17) 
    {
      buttonState17 = reading;
      if (buttonState17 == HIGH) 
      {
        metasuper=metasuper+1;
      }
      else
      {
	      metasuper=metasuper-1;
      }
    }
  }

  lastButtonState17 = reading;

  // Now the SUPER key
  reading = digitalRead(buttonPin18);

  if (reading != lastButtonState18) 
  {
    lastDebounceTime18 = millis();
  }

  if ((millis() - lastDebounceTime18) > debounceDelay) 
  {
    if (reading != buttonState18) 
    {
      buttonState18 = reading;
      if (buttonState18 == HIGH) 
      {
        metasuper=metasuper+2;
      }
      else
      {
        metasuper=metasuper-2;
      }
    }
  }

  lastButtonState18 = reading;

  // Time to strobe the current column and deal with what pops out
  switch(currentCol)
  {
  case 1:
    // This is the first column. Pull the column pin high to activate it.
    digitalWrite(colPin1, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState1) 
    {
      lastDebounceTime1 = millis();
    }
    if ((millis() - lastDebounceTime1) > debounceDelay) 
    {
      if (reading != buttonState1) 
      {
        buttonState1 = reading;
        if (buttonState1 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][0]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][0]);
        }
      }
    }
    lastButtonState1 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState5) 
    {
      lastDebounceTime5 = millis();
    }
    if ((millis() - lastDebounceTime5) > debounceDelay) 
    {
      if (reading != buttonState5) 
      {
        buttonState5 = reading;
        if (buttonState5 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][4]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][4]);
        }
      }
    } 
    lastButtonState5 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState9) 
    {
      lastDebounceTime9= millis();
    }
    if ((millis() - lastDebounceTime9) > debounceDelay) 
    {
      if (reading != buttonState9) 
      {
        buttonState9 = reading;
        if (buttonState9 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][8]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][8]);
        }
      }
    }
    lastButtonState9 = reading;
    
    reading = digitalRead(rowPin4);
    if (reading != lastButtonState13) 
    {
      lastDebounceTime13 = millis();
    }
    if ((millis() - lastDebounceTime13) > debounceDelay) 
    {
      if (reading != buttonState13) 
      {
        buttonState13 = reading;
        if (buttonState13 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][12]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][12]);
        }
      }
    }
    lastButtonState13 = reading;

    // now pull the pin back dwon.
    digitalWrite(colPin1, LOW);

  case 2:
    // this is column 2
    digitalWrite(colPin2, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState2) 
    {
      lastDebounceTime2 = millis();
    }
    if ((millis() - lastDebounceTime2) > debounceDelay) 
    {
      if (reading != buttonState2) 
      {
        buttonState2 = reading;
        if (buttonState2 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][1]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][1]);
        }
      }
    }
    lastButtonState2 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState6) 
    {
      lastDebounceTime6 = millis();
    }
    if ((millis() - lastDebounceTime6) > debounceDelay) 
    {
      if (reading != buttonState6) 
      {
        buttonState6 = reading;
        if (buttonState6 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][5]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][5]);
        }
      }
    } 
    lastButtonState6 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState10) 
    {
      lastDebounceTime10 = millis();
    }
    if ((millis() - lastDebounceTime10) > debounceDelay) 
    {
      if (reading != buttonState10) 
      {
        buttonState10 = reading;
        if (buttonState10 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][9]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][9]);
        }
      }
    }
    lastButtonState10 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState14) 
    {
      lastDebounceTime8 = millis();
    }
    if ((millis() - lastDebounceTime14) > debounceDelay) 
    {
      if (reading != buttonState14) 
      {
        buttonState14 = reading;
        if (buttonState14 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][13]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][13]);
        }
      }
    }
    lastButtonState14 = reading;

    digitalWrite(colPin2, LOW);

  case 3:
    // The third column
    digitalWrite(colPin3, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState3) 
    {
      lastDebounceTime3 = millis();
    }
    if ((millis() - lastDebounceTime3) > debounceDelay) 
    {
      if (reading != buttonState3) 
      {
        buttonState3 = reading;
        if (buttonState3 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][2]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][2]);
        }
      }
    }
    lastButtonState3 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState7) 
    {
      lastDebounceTime7 = millis();
    }
    if ((millis() - lastDebounceTime7) > debounceDelay) 
    {
      if (reading != buttonState7) 
      {
        buttonState7 = reading;
        if (buttonState7 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][6]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][6]);
        }
      }
    } 
    lastButtonState7 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState11) 
    {
      lastDebounceTime11 = millis();
    }
    if ((millis() - lastDebounceTime11) > debounceDelay) 
    {
      if (reading != buttonState11) 
      {
        buttonState11 = reading;
        if (buttonState11 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][10]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][10]);
        }
      }
    }
    lastButtonState11 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState15) 
    {

      lastDebounceTime15 = millis();
    }
    if ((millis() - lastDebounceTime15) > debounceDelay) 
    {
      if (reading != buttonState15) 
      {
        buttonState15 = reading;
        if (buttonState15 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][14]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][14]);
        }
      }
    }
    lastButtonState15 = reading;

    digitalWrite(colPin3, LOW);

  case 4:
    // The final column
    digitalWrite(colPin4, HIGH);
    reading = digitalRead(rowPin1);
    if (reading != lastButtonState4) 
    {
      lastDebounceTime4 = millis();
    }
    if ((millis() - lastDebounceTime4) > debounceDelay) 
    {
      if (reading != buttonState4) 
      {
        buttonState4 = reading;
        if (buttonState4 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][3]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][3]);
        }
      }
    }
    lastButtonState4 = reading;

    reading = digitalRead(rowPin2);
    if (reading != lastButtonState8) 
    {
      lastDebounceTime8 = millis();
    }
    if ((millis() - lastDebounceTime8) > debounceDelay) 
    {
      if (reading != buttonState8) 
      {
        buttonState8 = reading;
        if (buttonState8 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][7]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][7]);
        }
      }
    } 
    lastButtonState8 = reading;

    reading = digitalRead(rowPin3);
    if (reading != lastButtonState12) 
    {
      lastDebounceTime12 = millis();
    }
    if ((millis() - lastDebounceTime12) > debounceDelay) 
    {
      if (reading != buttonState12) 
      {
        buttonState12 = reading;
        if (buttonState12 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][11]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][11]);
        }
      }
    }
    lastButtonState12 = reading;

    reading = digitalRead(rowPin4);
    if (reading != lastButtonState16) 
    {
      lastDebounceTime16 = millis();
    }
    if ((millis() - lastDebounceTime16) > debounceDelay) 
    {
      if (reading != buttonState16) 
      {
        buttonState16 = reading;
        if (buttonState16 == HIGH) 
        {
          Keyboard.pressRaw(keycharmap[metasuper][15]);
        }
	else
        {
	        Keyboard.releaseRaw(keycharmap[metasuper][15]);
        }
      }
    }
    lastButtonState16 = reading;

    digitalWrite(colPin4, LOW);
  }

  // Increment the current column number. roll it over if needed
  currentCol++;
  if (currentCol==5)
  {
    currentCol=1;
  }
  
  // Process the rotary encoders
  if (rotaryRcount == 1)
  {
    Keyboard.consumerPress(KEY_VOLUME_INCREMENT);
    rotaryRcount = 0;
    Keyboard.consumerRelease();
  }
  if (rotaryRcount == -1)
  {
    Keyboard.consumerPress(KEY_VOLUME_DECREMENT);
    rotaryRcount = 0;
    Keyboard.consumerRelease();
  }
    if (rotaryLcount == 1)
  {
    Mouse.move(0,0,MOUSE_SCROLL_AMOUNT);
    rotaryLcount = 0;
  }
    if (rotaryLcount == -1)
  {
    Mouse.move(0,0,MOUSE_SCROLL_AMOUNT*-1);
    rotaryLcount = 0;
  }

  // Update the OLED based on the state of META and SUPER
  if(metasuper != lastmetasuper)
  {
    display.clearDisplay();
    if(metasuper == 1)
    {
      display.drawBitmap(0, 0, image_data_META, 128, 32, 1);
    }
    if(metasuper == 2)
    {
      display.drawBitmap(0, 0, image_data_SUPER, 128, 32, 1);
    }
    if(metasuper == 3)
    {
      display.drawBitmap(0, 0, image_data_SNM, 128, 32, 1);
    }
    display.display(); 
  }
  lastmetasuper=metasuper;
}

// rotate is called anytime the rotary inputs change state.
void rotateL() 
{
  unsigned char result = rotaryL.process();
  if (result == DIR_CW) 
  {
    rotaryLcount = 1;
  } else if (result == DIR_CCW) 
  {
    rotaryLcount = -1;
  }
}

void rotateR() 
{
  unsigned char result = rotaryR.process();
  if (result == DIR_CW) 
  {
    rotaryRcount = 1;
  } else if (result == DIR_CCW) 
  {
    rotaryRcount = -1;
  }
}