/*
 * CommandHandler.cpp
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include "ESP32/CommandHandler.h"
#include <algorithm>
#include <ESP32/Exceptions/CommandHandlerExceptions.h>
#include <ESP32/ESP32ProtocolConstants.h>

namespace ESP32 {

CommandHandler::CommandHandler(ICommandContainer* commandList, Communication& communicator) :
	commandList_(commandList),
	communicator_(communicator)
{

}

uint16_t CommandHandler::Handle(uint8_t* msg, uint32_t count)
{
	try {
		Command cmd = ParseMessage(msg,count);
		ProcessCommand(cmd);
	} catch (...) /*TODO: Specify exceptions*/{
		throw;	// rethrow
	}
	return 0;
}

void CommandHandler::ProcessCommand(Command& cmd)
{
	for (ICommandProcessor** it = commandList_->begin(); it != commandList_->end(); it++){
		if ((*it)->GetCode() == cmd.code){
			(*(*it))(communicator_,cmd);
			break;	// Dont allow multiple handlers to handle!
		}
	}

}


Command CommandHandler::ParseMessage(uint8_t* msg, uint32_t count)
{
	/* Find start and end */
	uint8_t* start 	= nullptr;
	uint8_t* end 	= nullptr;
	for (uint8_t* msgIt = msg; msgIt < msg+count; msgIt++ ){
		if (*msgIt==k_StartCharacter && start==nullptr)
			start = msgIt;
		if (*msgIt==k_EndCharacter && end==nullptr)
			end = msgIt;
	}

	if (start==nullptr || end==nullptr)
		throw InvalidCommand();

	// TODO: Packed attribute is potentially unsafe
	Command tmp = *(reinterpret_cast<Command*>(start+1));

	return tmp;
}

CommandHandler::~CommandHandler() {
	// TODO Auto-generated destructor stub
}

} /* namespace ESP32 */
