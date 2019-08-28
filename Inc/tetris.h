/*
 * tetris.h
 *
 *  Created on: Aug 14, 2019
 *      Author: naoki
 */

#include "main.h"
#include <controlLed.h>
#ifndef TETRIS_H_
#define TETRIS_H_
#include <stdlib.h>


void playTetris();
void displayBoard();
void newBlock();
int getBottom();
int getLeft();
int getRight();
int fallBlock();
int leftBlock();
int rightBlock();
void fixedBlock();
void turnBlock();
int checkBlock();
int deleteLine();
int gameOver();

extern uint8_t monitor[20][10];//6bit目から2bitずつR G B







#endif /* TETRIS_H_ */
