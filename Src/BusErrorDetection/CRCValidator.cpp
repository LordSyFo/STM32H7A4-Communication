/*
 * CRCValidator.cpp
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <BusErrorDetection/CRCValidator.h>

namespace BusErrorDetection{


CRCValidator::CRCValidator(CRC_HandleTypeDef* crcHandle) : crcHandle_(crcHandle) {
	// TODO Auto-generated constructor stub

}

/*
 * Determine if a message has a valid CRC.
 *
 * Use this to determine if a received message has a valid CRC.
 *
 * @param ´buffer´ 	Pointer to message.
 * @param ´len´ 	Length of message.
 * @return True if the message is deemed valid, false otherwise.
 * */
bool CRCValidator::IsValid(uint8_t* buffer, uint32_t len) const
{
	return HAL_CRC_Calculate(crcHandle_, (uint32_t*)buffer, len) == 0;
}

/*
 * Compute CRC-code from a message-buffer.
 *
 * Use this to determine compute a CRC from a message-buffer using the specific validators error detection method.
 *
 * @param ´buffer´ 	Pointer to message.
 * @param ´len´ 	Length of message.
 * @return Error detection code.
 * */
uint32_t CRCValidator::ComputeCode(uint8_t* buffer, uint32_t len)
{
	uint16_t code = HAL_CRC_Calculate(crcHandle_, (uint32_t*)buffer, len);

	// Convert from Little endian to big endian
	uint16_t bigCode = (code >> 8) | (code<<8);

	return bigCode;
}

CRCValidator::~CRCValidator() {
	// TODO Auto-generated destructor stub
}

}
