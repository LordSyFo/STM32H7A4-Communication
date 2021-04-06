/*
 * VersionProcessor.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMANDPROCESSORS_VERSIONPROCESSOR_H_
#define INC_ESP32_COMMANDPROCESSORS_VERSIONPROCESSOR_H_

#include <ESP32/CommandProcessors/ICommandProcessor.h>
#include <Util/Version.h>
#include <stdio.h>

namespace ESP32 {

class VersionProcessor: public ICommandProcessor {
public:
	VersionProcessor() {}

	void operator()(ICommunication& communicator, Command& cmd)
	{
		uint8_t response[] = {Version::kMajor, Version::kMinor, Version::kPatch};
		communicator.WriteSync(response, sizeof(response),10000);	// Size without terminating null
	}

	uint8_t GetCode() const { return 0x13; }

	virtual ~VersionProcessor() {}
};

} /* namespace ESP32 */

#endif /* INC_ESP32_COMMANDPROCESSORS_VERSIONPROCESSOR_H_ */

