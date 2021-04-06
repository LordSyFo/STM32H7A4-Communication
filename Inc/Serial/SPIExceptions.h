/*
 * SPIExceptions.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_SERIAL_SPIEXCEPTIONS_H_
#define INC_SERIAL_SPIEXCEPTIONS_H_

#include <Util/BaseException.h>

class SPIException : public BaseException { };

class AsyncReceptionError : public SPIException {};
class AsyncTransmissionError : public SPIException {};
class TimeoutError : public SPIException {};



#endif /* INC_SERIAL_SPIEXCEPTIONS_H_ */
