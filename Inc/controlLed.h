/*
 * controlLed.hpp
 *
 *  Created on: Jul 16, 2019
 *      Author: naoki
 */


#include "main.h"
#ifndef CONTROLLED_HPP_
#define CONTROLLED_HPP_

extern uint8_t monitor[20][10];//6bit目から2bitずつR G B
extern uint8_t spi_data[2400];
#define LED_LIGHT 5
void writeLED();
int leftButton();
int upButton();
int downButton();
int rightButton();


#endif /* CONTROLLED_HPP_ */
