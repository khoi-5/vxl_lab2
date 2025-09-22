/*
 * software_timer.h
 *
 *  Created on: Sep 22, 2025
 *      Author: DELL
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

int timer_flag[10];
int timer_counter[10];
int timer_cycle = 10;
void setTimer(int index, int counter) {
	timer_flag[index] = 0;
	timer_counter[index] = counter / timer_cycle;
}
void timerRun() {
	for (int i = 0; i < 10; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
		}
		if (timer_counter[i] <= 0) {
			timer_flag[i] = 1;
		}
	}
}


#endif /* INC_SOFTWARE_TIMER_H_ */
