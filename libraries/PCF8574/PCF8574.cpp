/*
 * See header file for details
 *
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * 
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * 
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */

/* Dependencies */
#include <Wire.h>
#include "PCF8574.h"
#ifdef PCF8574_INTERRUPT_SUPPORT
//#include "PCint.h"
#endif

PCF8574::PCF8574() :
		_PORT(0), _PIN(0), _DDR(0), _address(0)
#ifdef PCF8574_INTERRUPT_SUPPORT
		, _oldPIN(0), _isrIgnore(0), _pcintPin(0), _intMode(), _intCallback()
#endif
{
}

void PCF8574::begin(uint8_t address) {

	/* Store the I2C address and init the Wire library */
	_address = address;
	Wire.begin();
	readGPIO();
}

void PCF8574::pinMode(uint8_t pin, uint8_t mode) {

	/* Switch according mode */
	switch (mode) {
	case INPUT:
		_DDR &= ~(1 << pin);
		_PORT &= ~(1 << pin);
		break;

	case INPUT_PULLUP:
		_DDR &= ~(1 << pin);
		_PORT |= (1 << pin);
		break;

	case OUTPUT:
		_DDR |= (1 << pin);
		_PORT &= ~(1 << pin);
		break;

	default:
		break;
	}

	/* Update GPIO values */
	updateGPIO();
}

void PCF8574::digitalWrite(uint8_t pin, uint8_t value) {

	/* Set PORT bit value */
	if (value)
		_PORT |= (1 << pin);
	else
		_PORT &= ~(1 << pin);

	/* Update GPIO values */
	updateGPIO();
}

uint8_t PCF8574::digitalRead(uint8_t pin) {

	/* Read GPIO */
	readGPIO();

#ifdef PCF8574_INTERRUPT_SUPPORT
	/* Check for interrupt (manual detection) */
	//checkForInterrupt();
#endif

	/* Read and return the pin state */
	return (_PIN & (1 << pin)) ? HIGH : LOW;
}

void PCF8574::write(uint8_t value) {

	/* Store pins values and apply */
	_PORT = value;

	/* Update GPIO values */
	updateGPIO();
}

uint8_t PCF8574::read() {

	/* Read GPIO */
	readGPIO();

#ifdef PCF8574_INTERRUPT_SUPPORT
	/* Check for interrupt (manual detection) */
	//checkForInterrupt();
#endif

	/* Return current pins values */
	return _PIN;
}

void PCF8574::pullUp(uint8_t pin) {

	/* Same as pinMode(INPUT_PULLUP) */
	pinMode(pin, INPUT_PULLUP); // /!\ pinMode form THE LIBRARY
}

void PCF8574::pullDown(uint8_t pin) {

	/* Same as pinMode(INPUT) */
	pinMode(pin, INPUT); // /!\ pinMode form THE LIBRARY
}

void PCF8574::clear() {

	/* User friendly wrapper for write() */
	write(0x00);
}

void PCF8574::set() {

	/* User friendly wrapper for write() */
	write(0xFF);
}

void PCF8574::toggle(uint8_t pin) {

	/* Toggle pin state */
	_PORT ^= (1 << pin);

	/* Update GPIO values */
	updateGPIO();
}

void PCF8574::blink(uint8_t pin, uint16_t count, uint32_t duration) {

	/* Compute steps duration */
	duration /= count * 2;

	/* Loop n times */
	while (count--) {

		/* Toggle pin 2 times */
		toggle(pin);
		delay(duration);
		toggle(pin);
		delay(duration);
	}
}

 

void PCF8574::readGPIO() {

#ifdef PCF8574_INTERRUPT_SUPPORT
	/* Store old _PIN value */
	_oldPIN = _PIN;
#endif

	/* Start request, wait for data and receive GPIO values as byte */
	Wire.requestFrom(_address, (uint8_t) 0x01);
	while (Wire.available() < 1)
		;
	_PIN = I2CREAD();
}

void PCF8574::updateGPIO() {

	/* Read current GPIO states */
	//readGPIO(); // Experimental

	/* Compute new GPIO states */
	//uint8_t value = ((_PIN & ~_DDR) & ~(~_DDR & _PORT)) | _PORT; // Experimental
	uint8_t value = (_PIN & ~_DDR) | _PORT;

	/* Start communication and send GPIO values as byte */
	Wire.beginTransmission(_address);
	I2CWRITE(value);
	Wire.endTransmission();
}
