/*
 * ESP32ProtocolConstants.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <stdint.h>

#ifndef INC_ESP32_COMMANDPROCESSORS_ESP32PROTOCOLCONSTANTS_H_
#define INC_ESP32_COMMANDPROCESSORS_ESP32PROTOCOLCONSTANTS_H_

constexpr uint8_t k_StartCharacter 	= 0x01;
constexpr uint8_t k_EndCharacter 	= 0x04;
constexpr uint8_t k_AckCharacter 	= 0x06;
constexpr uint8_t k_NakCharacter 	= 0x15;
constexpr uint8_t k_ReadCharacter 	= 0xff;
constexpr uint8_t k_FinCharacter 	= 0xfe;


#endif /* INC_ESP32_COMMANDPROCESSORS_ESP32PROTOCOLCONSTANTS_H_ */
