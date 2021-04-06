/*
 * Communication.cpp
 *
 *  Created on: 12 Oct 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <ESP32/Communication.h>
#include <ESP32/ESP32ProtocolConstants.h>
#include <cstring>
#include <ESP32/Exceptions/CommunicationExceptions.h>

namespace ESP32 {

Communication::Communication(Serial::SPI* spiHandle, BusErrorDetection::CRCValidator& validator) :
	spiHandle_(spiHandle),
	validator_(validator)
{
	// TODO Auto-generated constructor stub

}

void Communication::WriteAsync(const uint8_t* response, uint32_t count)
{
	if (count > MAX_COMMAND_SIZE-4) return;	// TODO: Throw

	//TODO: This could be done more pretty with sprintf but this might be a bit slower

	/* Build message */
	txBuffer_[0] = k_StartCharacter;			// Set start character
	memcpy(txBuffer_+1, response, count);	// Copy actual message
	txBuffer_[count+1] = k_EndCharacter;		// Set end character (+1 because of the startcharacter)

	/* Calculate and append CRC */
	uint32_t code = validator_.ComputeCode(txBuffer_, count+2);
	memcpy(txBuffer_+count+2, (uint8_t*)&code, 2);	// copy 16-bit crc code

	/* Write to SPI */
	spiHandle_->BeginWriteAsync(txBuffer_, count+4);
}

void Communication::WriteSync(const uint8_t* response, uint32_t count, uint32_t timeout)
{
	if (count > MAX_COMMAND_SIZE-4) return;	// TODO: Throw

	//TODO: This could be done more pretty with sprintf but this might be a bit slower

	/* Build message */
	txBuffer_[0] = k_StartCharacter;			// Set start character
	memcpy(txBuffer_+1, response, count);	// Copy actual message
	txBuffer_[count+1] = k_EndCharacter;		// Set end character (+1 because of the startcharacter)

	/* Calculate and append CRC */
	uint32_t code = validator_.ComputeCode(txBuffer_, count+2);
	memcpy(txBuffer_+count+2, (uint8_t*)&code, 2);	// copy 16-bit crc code

	/* Write to SPI */
	try {
		spiHandle_->Write(0, txBuffer_, count+4, timeout);
	} catch (...){
		throw;
	}
}

void Communication::ReadSync(uint8_t* recieved, uint32_t count, uint32_t timeout)
{
	try {
		spiHandle_->Read(0, rxBuffer_, count+4, timeout);

		if (!validator_.IsValid(rxBuffer_, count+4))
			throw CRCError();	// Throw if CRC is not valid!

		memcpy(recieved, rxBuffer_+1,count);
	} catch (...){
		throw;
	}
}


Communication::~Communication() {
	// TODO Auto-generated destructor stub
}

} /* namespace ESP32 */
