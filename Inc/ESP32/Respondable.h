/*
 * Respondable.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_RESPONDABLE_H_
#define INC_ESP32_RESPONDABLE_H_

namespace ESP32 {

class Respondable {
public:
	Respondable(){}

	virtual void Respond(uint8_t* response, uint32_t count) = 0;

	virtual ~Respondable(){}
};

} /* namespace ESP32 */

#endif /* INC_ESP32_RESPONDABLE_H_ */
