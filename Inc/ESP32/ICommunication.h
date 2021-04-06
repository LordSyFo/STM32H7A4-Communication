/*
 * ICommunication.h
 *
 *  Created on: 17 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_ICOMMUNICATION_H_
#define INC_ESP32_ICOMMUNICATION_H_

#include <stdint.h>

namespace ESP32 {

class ICommunication {
public:
	ICommunication(){}

	virtual void WriteAsync(const uint8_t* response, uint32_t count) = 0;
	virtual void WriteSync(const uint8_t* response, uint32_t count, uint32_t timeout) = 0;
	virtual void ReadSync(uint8_t* recieved, uint32_t count, uint32_t timeout) = 0;

	// Mirrored methods from SPI
	virtual void BeginReadAsync(uint8_t* data, const uint16_t count) = 0;
	virtual bool MessageReady() = 0;
	virtual uint32_t GetMessageLength() = 0;
	virtual void Reset() = 0;

	/* Error detection */
	virtual bool Validate(uint8_t* msg, uint32_t count) = 0;

	virtual ~ICommunication(){}
};

} /* namespace ESP32 */

#endif /* INC_ESP32_ICOMMUNICATION_H_ */
