/*
 * ESP32Interface.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_PROCESS_H_
#define INC_ESP32_PROCESS_H_

#include <Serial/SPI.h>
#include <Util/AProcess.h>
#include <ESP32/CommandHandler.h>
#include <ESP32/Respondable.h>
#include <ESP32/ICommunication.h>

namespace ESP32 {

enum class State {
	WaitingState = 0,
	RecievingState = 1,
	RecievedState = 2,
};

class Process : public Util::AProcess{
public:
	Process(ESP32::ICommunication& communicator, CommandHandler& cmdHandler);

	void HandleMessage(uint8_t* msg, uint32_t count);

	/* From AProcess */
	void Run();

	void OnEnter(){}
	void OnExit(){}

	void SuperLoop(); 	// Superloop (half state-machine not really suited for a thread)

	virtual ~Process();
private:
	static constexpr int kRXBufferSize_ = 50;
	uint8_t rxBuffer_[kRXBufferSize_];
	uint32_t rxRecievedCount_;

	State state_;

	CommandHandler& cmdHandler_;
	ESP32::ICommunication& communicator_;

	int x_;

};

} /* namespace ImageUtil */

#endif /* INC_ESP32_PROCESS_H_ */
