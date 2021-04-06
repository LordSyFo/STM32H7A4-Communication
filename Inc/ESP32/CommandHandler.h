/*
 * CommandHandler.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef SRC_ESP32_COMMANDHANDLER_H_
#define SRC_ESP32_COMMANDHANDLER_H_

#include <stdint.h>
#include <BusErrorDetection/CRCValidator.h>
#include <cstring>
#include <array>
#include <ESP32/CommandProcessors/CommandContainer.h>
#include <ESP32/Command.h>
#include <ESP32/Communication.h>

namespace ESP32 {

class CommandHandler {
public:

	CommandHandler( ICommandContainer* commandList,
	 Communication& communicator);

	uint16_t Handle(uint8_t* msg, uint32_t count);

	virtual ~CommandHandler();
private:
	ICommandContainer* commandList_;
	Communication& communicator_;

	void ProcessCommand(Command& cmd);

	/* Parser */
	Command ParseMessage(uint8_t* msg, uint32_t count);

};
} /* namespace ESP32 */

#endif /* SRC_ESP32_COMMANDHANDLER_H_ */
