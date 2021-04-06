/*
 * ICommandProcessor.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMANDPROCESSORS_ICOMMANDPROCESSOR_H_
#define INC_ESP32_COMMANDPROCESSORS_ICOMMANDPROCESSOR_H_

#include <ESP32/Respondable.h>
#include <ESP32/CommandHandler.h>
#include <ESP32/Command.h>
#include <ESP32/ICommunication.h>
#include <stdint.h>

namespace ESP32 {

class ICommandProcessor {
public:
	ICommandProcessor(){}

	virtual void operator()(ESP32::ICommunication& communicator,Command& cmd) = 0;
	virtual uint8_t GetCode() const = 0;

	virtual ~ICommandProcessor(){}
};

} /* namespace ESP32 */

#endif /* INC_ESP32_COMMANDPROCESSORS_ICOMMANDPROCESSOR_H_ */
