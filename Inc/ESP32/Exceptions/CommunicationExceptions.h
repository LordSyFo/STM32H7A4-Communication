/*
 * CommunicationExceptions.h
 *
 *  Created on: 13 Oct 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMUNICATIONEXCEPTIONS_H_
#define INC_ESP32_COMMUNICATIONEXCEPTIONS_H_

#include <Util/BaseException.h>

class CommunicationException : public BaseException { };

class CRCError : public CommunicationException {};


#endif /* INC_ESP32_COMMUNICATIONEXCEPTIONS_H_ */
