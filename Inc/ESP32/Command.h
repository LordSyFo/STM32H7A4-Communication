/*
 * Command.h
 *
 *  Created on: Oct 9, 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_ESP32_COMMAND_H_
#define INC_ESP32_COMMAND_H_

#define MAX_COMMAND_ARGUMENTS 62

typedef struct Command {
	uint8_t rw;
	uint8_t code;
	uint8_t arguments[MAX_COMMAND_ARGUMENTS];
} __attribute__((packed)) Command;

#endif /* INC_ESP32_COMMAND_H_ */
