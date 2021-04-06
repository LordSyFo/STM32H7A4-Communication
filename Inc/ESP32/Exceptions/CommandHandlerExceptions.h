/*
 * CommandHandlerExceptions.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <Util/BaseException.h>

#ifndef SRC_ESP32_COMMANDHANDLEREXCEPTIONS_H_
#define SRC_ESP32_COMMANDHANDLEREXCEPTIONS_H_

class CommandHandlerException : public BaseException { };

class InvalidCommand : public CommandHandlerException {};

#endif /* SRC_ESP32_COMMANDHANDLEREXCEPTIONS_H_ */
