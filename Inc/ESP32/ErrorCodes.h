/*
 * ErrorCodes.h
 *
 *  Created on: 19 Nov 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_ERRORCODES_H_
#define INC_ESP32_ERRORCODES_H_

namespace ESP32 {
namespace Errorcode{
	constexpr uint8_t k_InvalidIndex = 0x72;	// Used to indicate attempts at over or under indexing.
}
}



#endif /* INC_ESP32_ERRORCODES_H_ */
