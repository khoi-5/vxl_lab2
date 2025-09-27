/*
 * button.h
 *
 *  Created on: Sep 27, 2025
 *      Author: DELL
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

extern int button1_flag;
int isButton1Pressed();
int isButton1LongPressed();
void getKeyInput();

#endif /* INC_BUTTON_H_ */
