/*
 * Communication.h
 *
 *  Created on: 12 Oct 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMUNICATION_H_
#define INC_ESP32_COMMUNICATION_H_

#include <Serial/SPI.h>
#include <BusErrorDetection/CRCValidator.h>
#include <assert.h>
#include <ESP32/ICommunication.h>

#define MAX_COMMAND_SIZE 64
#define MAX_RECIEVE_SIZE 64

namespace ESP32 {

class Communication : public ICommunication {
public:
	Communication(Serial::SPI* spiHandle, BusErrorDetection::CRCValidator& validator);

	void WriteAsync(const uint8_t* response, uint32_t count);
	void WriteSync(const uint8_t* response, uint32_t count, uint32_t timeout);
	void ReadSync(uint8_t* recieved, uint32_t count, uint32_t timeout);

	// Mirrored methods from SPI
	void BeginReadAsync(uint8_t* data, const uint16_t count) {return spiHandle_->BeginReadAsync(data, count);}
	bool MessageReady() { return spiHandle_->MessageReady(); }
	uint32_t GetMessageLength() {return spiHandle_->GetMessageLength();}
	void Reset() {return spiHandle_->Reset();}

	/* Error detection */
	bool Validate(uint8_t* msg, uint32_t count){
		return validator_.IsValid(msg, count);
	}


	virtual ~Communication();

private:
	Serial::SPI* spiHandle_;
	BusErrorDetection::CRCValidator& validator_;

	uint8_t txBuffer_[MAX_COMMAND_SIZE];
	uint8_t rxBuffer_[MAX_RECIEVE_SIZE];

};

} /* namespace ESP32 */

#endif /* INC_ESP32_COMMUNICATION_H_ */
