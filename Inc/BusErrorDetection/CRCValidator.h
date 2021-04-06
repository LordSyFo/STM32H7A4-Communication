/*
 * CRCValidator.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_BUSERRORDETECTION_CRCVALIDATOR_H_
#define INC_BUSERRORDETECTION_CRCVALIDATOR_H_

#include <BusErrorDetection/IValidator.h>
#include "stm32h7xx_hal.h"

namespace BusErrorDetection{

class CRCValidator : public IValidator{
public:
	CRCValidator(CRC_HandleTypeDef* crcHandle);

	bool IsValid(uint8_t* buffer, uint32_t len) const;

	uint32_t ComputeCode(uint8_t* buffer, uint32_t len);

	/*
	 * Get the CRC length in bytes.
	 *
	 * Use this to determine the length of the used CRC.
	 *
	 * @return Length of the used CRC in bytes.
	 * */
	uint32_t GetCodeLength() const { return 2; };	// 16 bit = 2 bytes

	virtual ~CRCValidator();

private:
	CRC_HandleTypeDef* crcHandle_;
};


}

#endif /* INC_BUSERRORDETECTION_CRCVALIDATOR_H_ */
