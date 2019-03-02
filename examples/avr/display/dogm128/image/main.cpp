/*
 * Copyright (c) 2010-2011, Fabian Greif
 * Copyright (c) 2012-2015, 2017-2018, Niklas Hauser
 * Copyright (c) 2014, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/platform.hpp>
#include <modm/driver/display/ea_dog.hpp>
#include <modm/architecture/interface/clock.hpp>

#include "images/image_64x64_0.hpp"
#include "images/image_64x64_1.hpp"
#include "images/image_64x64_2.hpp"
#include "images/image_64x64_3.hpp"
#include "images/image_64x64_4.hpp"
#include "images/image_64x64_5.hpp"
#include "images/image_64x64_6.hpp"
#include "images/image_64x64_7.hpp"
#include "images/image_64x64_8.hpp"
#include "images/image_64x64_9.hpp"

using namespace modm::platform;
using namespace modm::literals;

using systemClock = SystemClock;

namespace led
{
	typedef GpioOutputD7 R;
	typedef GpioOutputD6 G;
	typedef GpioOutputD5 B;
}

// define the pins used by the LCD
namespace lcd
{
	typedef GpioOutputB7 Sck;
	typedef GpioOutputB5 Mosi;

	typedef GpioOutputD2 Cs;
	typedef GpioOutputD3 A0;
	typedef GpioOutputD4 Reset;

	typedef BitBangSpiMaster< Sck, Mosi > SPI;
}

modm::DogM128< lcd::SPI, lcd::Cs, lcd::A0, lcd::Reset, true > display;

FLASH_STORAGE(uint8_t bootscreen[]) =
{
	128, 64,
	0xf0, 0xfc, 0x1e, 0x06, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb,
	0x7b, 0x7b, 0xfb, 0xfb, 0xf3, 0xf3, 0xf3, 0xe3, 0xc3, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0xe3, 0xf3, 0xf3,
	0xfb, 0xfb, 0xfb, 0xfb, 0x7b, 0x7b, 0xfb, 0xfb, 0xfb, 0xfb,
	0xf3, 0xf3, 0xe3, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0xc3, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb, 0xfb,
	0xfb, 0xfb, 0xfb, 0xc3, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x07, 0x06, 0x1e, 0xfc, 0xf0,
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xc0, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x3f,
	0x3f, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x1f, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x03, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xc0, 0xc0, 0xfe, 0xfe, 0xfe, 0xfe,
	0xfe, 0xfe, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3c, 0x3c, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0xff, 0xff, 0x08, 0x08, 0x08, 0xe8, 0x28, 0x28, 0x28, 0xc8,
	0x08, 0x08, 0x88, 0x88, 0x88, 0x08, 0x08, 0xe8, 0x08, 0x88,
	0x88, 0x08, 0x08, 0x08, 0x88, 0x88, 0x88, 0x08, 0x08, 0x88,
	0xe8, 0x88, 0x08, 0x0b, 0x0b, 0x0b, 0x8b, 0x8b, 0x8b, 0x0b,
	0x08, 0x88, 0x0b, 0x8b, 0x8b, 0x0b, 0x0b, 0xcb, 0x2b, 0x28,
	0x28, 0x48, 0x08, 0xe8, 0x08, 0x88, 0x08, 0x08, 0x09, 0x89,
	0x0b, 0xeb, 0x0b, 0x8b, 0x8b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
	0xc9, 0x29, 0x28, 0x28, 0xc8, 0x08, 0x08, 0x88, 0x88, 0x88,
	0x0b, 0x0b, 0x0b, 0x8b, 0x8b, 0x8b, 0x0b, 0x08, 0xe8, 0x0b,
	0x8b, 0x8b, 0x0b, 0x0b, 0x0b, 0x8b, 0x88, 0x88, 0x08, 0x08,
	0x88, 0x08, 0x88, 0x88, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
	0x88, 0x88, 0x88, 0x08, 0x08, 0x08, 0x08, 0xe8, 0x08, 0x08,
	0x08, 0xe8, 0x08, 0x08, 0x08, 0x08, 0xff, 0xff,
	0xff, 0xff, 0x20, 0x20, 0x20, 0x2f, 0x21, 0x23, 0x25, 0x28,
	0x20, 0x27, 0x28, 0x28, 0x28, 0x27, 0x20, 0x2f, 0x29, 0x28,
	0x28, 0x27, 0x20, 0x27, 0xa8, 0xa8, 0xa8, 0xa7, 0xa0, 0xa0,
	0xa7, 0xa8, 0xa8, 0xa4, 0xa0, 0x27, 0x2a, 0x2a, 0x2a, 0x23,
	0x20, 0x2f, 0x21, 0xe0, 0x20, 0x21, 0x20, 0x27, 0x28, 0x28,
	0x28, 0x24, 0x20, 0x2f, 0x20, 0x27, 0x28, 0x28, 0x24, 0x2f,
	0x20, 0x2f, 0x29, 0x28, 0x28, 0x27, 0x20, 0x20, 0x20, 0x20,
	0x2f, 0x22, 0x22, 0x22, 0x2f, 0x20, 0x24, 0x2a, 0x2a, 0x2a,
	0x2f, 0x20, 0x27, 0x28, 0xe8, 0x28, 0x24, 0x20, 0x2f, 0x21,
	0x20, 0xa0, 0xaf, 0xa0, 0xa7, 0xaa, 0xaa, 0xaa, 0xa3, 0xa0,
	0xaf, 0xa1, 0xa0, 0xa0, 0xaf, 0xa0, 0xa0, 0xa0, 0xa0, 0xa7,
	0xaa, 0xaa, 0xaa, 0xa1, 0xa0, 0xa8, 0xa0, 0xa3, 0x24, 0x28,
	0x24, 0x23, 0x28, 0x20, 0x20, 0x20, 0xff, 0xff,
	0xff, 0xff, 0x82, 0x82, 0x82, 0xe2, 0x22, 0x22, 0x22, 0x22,
	0x22, 0x22, 0x22, 0x22, 0xe2, 0x82, 0x82, 0x82, 0xc2, 0xc2,
	0xc2, 0x82, 0x82, 0x82, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfe, 0x10, 0x10, 0x10,
	0x10, 0x10, 0x10, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x07, 0x0f, 0x1f, 0x3f, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0x80, 0xa4, 0xaa, 0xaa, 0x92, 0x80, 0x82, 0xbe,
	0x82, 0x80, 0xbc, 0x92, 0x92, 0xbc, 0x80, 0xbe, 0x8a, 0x9a,
	0xac, 0x80, 0x82, 0xbe, 0x82, 0x80, 0x80, 0xff, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff,
	0xff, 0xff, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x03, 0xa0, 0xa0, 0xa0, 0xa1, 0xbf,
	0xa1, 0xa0, 0xa0, 0xa0, 0x03, 0x02, 0x02, 0x02, 0x02, 0x02,
	0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x3e, 0x7e, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xe0,
	0xe0, 0xe0, 0xe0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0x80, 0x40, 0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x28,
	0xe4, 0x24, 0x02, 0x42, 0x41, 0x02, 0x42, 0x24, 0xa4, 0x48,
	0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff,
	0x0f, 0x3f, 0x78, 0x68, 0xe8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8,
	0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xdc, 0xdf,
	0xdc, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8,
	0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8, 0xc8,
	0xc8, 0xc8, 0xc8, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xc0, 0xc1, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
	0xc3, 0xc7, 0xcf, 0xdf, 0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf1,
	0xe3, 0xc7, 0xcf, 0xdf, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0,
	0xe0, 0xc0, 0xc0, 0xc0, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc1, 0xc1, 0xc2, 0xc2, 0xc4, 0xc4, 0xc8, 0xca,
	0xd3, 0xd2, 0xe0, 0xe1, 0xc1, 0xe0, 0xe2, 0xd3, 0xd2, 0xca,
	0xc8, 0xc4, 0xc4, 0xc2, 0xc2, 0xc1, 0xc1, 0xc0, 0xc0, 0xc0,
	0xc0, 0xc0, 0xc0, 0xe0, 0x60, 0x78, 0x3f, 0x0f,
};

void
drawNumber(modm::glcd::Point cursor, uint8_t number)
{
	switch (number)
	{
		case 0:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_0));
			break;
		case 1:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_1));
			break;
		case 2:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_2));
			break;
		case 3:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_3));
			break;
		case 4:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_4));
			break;
		case 5:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_5));
			break;
		case 6:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_6));
			break;
		case 7:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_7));
			break;
		case 8:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_8));
			break;
		case 9:
			display.drawImage(cursor, modm::accessor::asFlash(bitmap::image_64x64_9));
			break;
	}
}

int
main()
{
	led::R::set();
	led::G::set();
	led::B::reset();

	led::R::setOutput();
	led::G::setOutput();
	led::B::setOutput();

	lcd::SPI::connect<lcd::Sck::BitBang, lcd::Mosi::BitBang>();
	lcd::SPI::initialize<systemClock, 2_MHz>();

	display.initialize();

	display.drawImage(modm::glcd::Point(0, 0), modm::accessor::asFlash(bootscreen));
	display.update();

	modm::delayMilliseconds(1500);

	uint8_t units = 0;
	uint8_t tens = 0;
	while (1)
	{
		units++;
		if (units >= 10) {
			units = 0;
			tens++;
			if (tens >= 10) {
				tens = 0;
			}
		}

		drawNumber(modm::glcd::Point(0, 0), tens);
		drawNumber(modm::glcd::Point(64, 0), units);
		display.update();

		modm::delayMilliseconds(200);
	}
}
