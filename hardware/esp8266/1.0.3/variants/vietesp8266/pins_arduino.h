/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis
  Modified for ESP8266 platform by Ivan Grokhotkov, 2014-2015.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h
#define VIET_ESP8266_V1
#define VIET_OFFSET_PIN       100

#define EXTERNAL_NUM_INTERRUPTS 16
#define NUM_DIGITAL_PINS        17
#define NUM_ANALOG_INPUTS       1

#define isFlashInterfacePin(p)      ((p) >= 6 && (p) <= 11)

#define analogInputToDigitalPin(p)  ((p > 0)?NOT_A_PIN:0)
#define digitalPinToInterrupt(p)    (((p) < EXTERNAL_NUM_INTERRUPTS)?p:NOT_A_PIN)
#define digitalPinHasPWM(p)         (((p) < NUM_DIGITAL_PINS)?p:NOT_A_PIN)

static const uint8_t SDA = 4;
static const uint8_t SCL = 5;

static const uint8_t SS    = 15;
static const uint8_t MOSI  = 13;
static const uint8_t MISO  = 12;
static const uint8_t SCK   = 14;

// static const uint8_t LED_BUILTIN = 14;
// static const uint8_t BUILTIN_LED = 14;

static const uint8_t ADC = 17;

// I2C analog pin ADS1115
static const uint8_t A0 = 17;
static const uint8_t A1 = 18;
static const uint8_t A2 = 19;
static const uint8_t A3 = 20;
static const uint8_t A4 = 21;

static const uint8_t D7   = 0 + VIET_OFFSET_PIN;
static const uint8_t D8   = 1 + VIET_OFFSET_PIN;
static const uint8_t D9   = 2 + VIET_OFFSET_PIN;
static const uint8_t D10  = 3 + VIET_OFFSET_PIN;
static const uint8_t D11  = 4 + VIET_OFFSET_PIN;
static const uint8_t D12  = 5 + VIET_OFFSET_PIN;
static const uint8_t D13  = 6 + VIET_OFFSET_PIN;

#define IO_0      0
#define IO_1      1
#define IO_2      2
#define IO_3      3
#define IO_4      4
#define IO_5      5
#define IO_11     11
#define IO_12     12
#define IO_13     13
#define IO_14     14
#define IO_15     15
#define IO_16     16

// static const uint8_t IO_0   = 0;// flash
// static const uint8_t IO_1   = 1;//tx
// static const uint8_t IO_2   = 2;// tx2
// static const uint8_t IO_3   = 3;//rx
// static const uint8_t IO_4   = 4;//sda
// static const uint8_t IO_5   = 5;//scl

// static const uint8_t IO_11   = 11;
// static const uint8_t IO_12   = 12;
// static const uint8_t IO_13   = 13;
// static const uint8_t IO_14   = 14;
// static const uint8_t IO_15   = 15;
// static const uint8_t IO_16   = 16;

// uint8_t digital_pin_PGM[] = {
//   IO_2,
//   IO_0,
//   IO_15,
//   IO_16,
//   IO_13,
//   IO_12,
//   IO_14
// };

// const uint8_t xyz[] PROGMEM = {
//   0x53, 0x61, 0x79, 0x20, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20,
//   0x74, 0x6f, 0x20, 0x4d, 0x79, 0x20, 0x4c, 0x69, 0x74, 0x74,
//   0x6c, 0x65, 0x20, 0x46, 0x72, 0x69, 0x65, 0x6e, 0x64, 0x00
// };
// ////=============================================
// // static const uint8_t A0 = 17; // old adc
// static const uint8_t ADC = 17;

// // I2C analog pin ADS1115
// static const uint8_t A0 = 18;
// static const uint8_t A1 = 19;
// static const uint8_t A2 = 20;
// static const uint8_t A3 = 21;

// static const uint8_t D0   = 0;// flash
// static const uint8_t D1   = 1;//tx
// static const uint8_t D2   = 2;// tx2
// static const uint8_t D3   = 3;//rx
// static const uint8_t D4   = 4;//sda
// static const uint8_t D5   = 5;//scl
// static const uint8_t RX   = 3;
// static const uint8_t TX   = 1;
// static const uint8_t D11   = 11;
// static const uint8_t D12   = 12;
// static const uint8_t D13   = 13;
// static const uint8_t D14   = 14;
// static const uint8_t D15   = 15;
// static const uint8_t D16   = 16;

////=============================================
// static const uint8_t D0   = 16;
// static const uint8_t D1   = 5;
// static const uint8_t D2   = 4;
// static const uint8_t D3   = 0;
// static const uint8_t D4   = 2;
// static const uint8_t D5   = 14;
// static const uint8_t D6   = 12;
// static const uint8_t D7   = 13;
// static const uint8_t D8   = 15;
// static const uint8_t RX   = 3;
// static const uint8_t TX   = 1;



// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR        Serial
#define SERIAL_PORT_USBVIRTUAL     Serial
#define SERIAL_PORT_HARDWARE       Serial
#define SERIAL_PORT_HARDWARE_OPEN  Serial

#ifdef LED_BUILTIN
#ifdef __cplusplus
extern "C"
#endif
const int BUILTIN_LED __attribute__((deprecated("use LED_BUILTIN"), weak)) = LED_BUILTIN;
#endif

#endif /* Pins_Arduino_h */
