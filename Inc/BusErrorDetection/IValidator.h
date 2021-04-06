/*
 * IValidator.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_BUSERRORDETECTION_IVALIDATOR_H_
#define INC_BUSERRORDETECTION_IVALIDATOR_H_

#include <stdint.h>

namespace BusErrorDetection{

class IValidator {
public:
	IValidator(){}

	/*
	 * Determine if a message is valid.
	 *
	 * Use this to determine if a received message is valid compared to the validators error detection method.
	 *
	 * @param ´buffer´ 	Pointer to message.
	 * @param ´len´ 	Length of message.
	 * @return True if the message is deemed valid, false otherwise.
	 * */
	virtual bool IsValid(uint8_t* buffer, uint32_t len) const  = 0;

	/*
	 * Compute error-detection code from a message-buffer.
	 *
	 * Use this to determine compute an error-detection code from a message-buffer using the specific validators error detection method.
	 *
	 * @param ´buffer´ 	Pointer to message.
	 * @param ´len´ 	Length of message.
	 * @return Error detection code.
	 * */
	virtual uint32_t ComputeCode(uint8_t* buffer, uint32_t len) = 0;

	/*
	 * Get the code length in bytes.
	 *
	 * Use this to determine the length of the specific error detection code.
	 *
	 * @return Length of the error detection code in bytes.
	 * */
	virtual uint32_t GetCodeLength() const = 0;

	virtual ~IValidator(){}
};

}
#endif /* INC_BUSERRORDETECTION_IVALIDATOR_H_ */
