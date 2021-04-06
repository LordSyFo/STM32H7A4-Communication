/*
 * ESP32Interface.cpp
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <ESP32/Process.h>
#include <Thread/Events/Events.hpp>
#include <Util/BaseException.h>

extern osSemaphoreId_t g_Semaphore;

namespace ESP32 {

Process::Process(ESP32::ICommunication& communicator, CommandHandler& cmdHandler) :
		communicator_(communicator),
		state_(State::WaitingState),
		cmdHandler_(cmdHandler)
{
}

void Process::Run()
{
	uint32_t flags;
	while(1){
		/* Start DMA transfer */
		try {
			communicator_.BeginReadAsync(rxBuffer_, kRXBufferSize_);
		} catch (BaseException e){

		}

		/* Wait for condition */
		osStatus_t status = Thread::Events::Wait(Thread::Events::SPISelectEvent);

		/* Enter critical section */
		// TODO: Disable Slaveselect interrupts! and enable at end!
		HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
		//osKernelLock();	// Lock kernel to prevent context switching

		// TODO: Handle hangs with timeout

		/* Attempt to handle message */
		communicator_.Reset();									// Reset the DMA buffer in the SPI module

		rxRecievedCount_ = communicator_.GetMessageLength();	// Save message length

		if (rxRecievedCount_>0)
			HandleMessage(rxBuffer_,rxRecievedCount_);

		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);	// Enable again

		/* Wait for response to be over */
		//osKernelUnlock();	// Unlock kernel

	}
}

void Process::SuperLoop(){
	/* State machine */
	switch (state_){
		case State::WaitingState:
			// Start ASYNC Read
			try {
				communicator_.BeginReadAsync(rxBuffer_, kRXBufferSize_);
				state_ = State::RecievingState;	// Update state if the read was successfully started
			} catch (...){
				break;
			}
			break;
		case State::RecievingState:
			// Wait for message to be recieved
			if (communicator_.MessageReady())
				state_ = State::RecievedState;	// Intentional fall through
			else
				break;
		case State::RecievedState:
			/* We reset here instead of inside the SPI-class' ISR Routine as this could cause deadlocks! */
			communicator_.Reset();									// Reset the DMA buffer in the SPI module
			rxRecievedCount_ = communicator_.GetMessageLength();	// Save message length

			HandleMessage(rxBuffer_,rxRecievedCount_);
			state_ = State::WaitingState;			// Wait for next message
			break;
	}
}

void Process::HandleMessage(uint8_t* msg, uint32_t count)
{
	// Check for bus errors
	if (!communicator_.Validate(msg, count)) return;

	// Attempt to parse and handle message
	try {
		// Commandhandler handles command and generates an appropriate response
		cmdHandler_.Handle(msg, count);

	} catch (...) {
		//TODO: Reply with appropriate error message
		return;
	}
}


Process::~Process() {
	// TODO Auto-generated destructor stub
}

} /* namespace ImageUtil */
