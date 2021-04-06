/*
 * CommandContainer.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMANDPROCESSORS_COMMANDCONTAINER_H_
#define INC_ESP32_COMMANDPROCESSORS_COMMANDCONTAINER_H_

#include <initializer_list>
#include <ESP32/CommandProcessors/ICommandProcessor.h>

namespace ESP32 {

class ICommandContainer {
public:
	ICommandContainer(){}

	virtual ICommandProcessor*& operator[](int i) = 0;

	virtual ICommandProcessor** begin() = 0;
	virtual ICommandProcessor** end() = 0;


	virtual ~ICommandContainer(){}

};

template<size_t SIZE>
class CommandContainer : public ICommandContainer {
public:
	template<typename ... T>
	CommandContainer(T... initList) : commands_{initList...}
	{
	}

	ICommandProcessor*& operator[](int i) {
		return commands_[i];
	}

	ICommandProcessor** begin() {return &commands_[0];}
	ICommandProcessor** end() {return &commands_[size_];}

	virtual ~CommandContainer(){}

private:
	int size_ = SIZE;
	ICommandProcessor* commands_[SIZE];

};

} /* namespace ESP32 */

#endif /* INC_ESP32_COMMANDPROCESSORS_COMMANDCONTAINER_H_ */
