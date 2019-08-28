/*
 * tetris.cpp
 *
 *  Created on: Aug 14, 2019
 *      Author: naoki
 */

#include "tetris.h"
uint8_t bord[24][10] = {};

uint8_t block[7][16] = {
		{
				0x81,0x00,0x00,0x00,//縦1列
				0x81,0x00,0x00,0x00,
				0x81,0x00,0x00,0x00,
				0x81,0x00,0x00,0x00
		},{
				0x00,0x00,0x00,0x00,//L型1
				0x82,0x00,0x00,0x00,
				0x82,0x00,0x00,0x00,
				0x82,0x82,0x00,0x00,
		},{
				0x00,0x00,0x00,0x00,//L型2
				0x00,0x83,0x00,0x00,
				0x00,0x83,0x00,0x00,
				0x83,0x83,0x00,0x00,
		},{
				0x00,0x00,0x00,0x00,//ずれ1
				0x00,0x00,0x00,0x00,
				0x84,0x84,0x00,0x00,
				0x00,0x84,0x84,0x00,
		},{
				0x00,0x00,0x00,0x00,//ずれ2
				0x00,0x00,0x00,0x00,
				0x00,0x85,0x85,0x00,
				0x85,0x85,0x00,0x00,
		},{
				0x00,0x00,0x00,0x00,//凸型
				0x86,0x00,0x00,0x00,
				0x86,0x86,0x00,0x00,
				0x86,0x00,0x00,0x00
		},{
				0x00,0x00,0x00,0x00,//□型
				0x00,0x00,0x00,0x00,
				0x87,0x87,0x00,0x00,
				0x87,0x87,0x00,0x00
		}

};

uint8_t blockVertical[2][16] = {
	{
		0x00,0x00,0x00,0x00,//縦1列
		0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,
		0x81,0x81,0x81,0x81
	},{
		0x81,0x00,0x00,0x00,//縦1列
		0x81,0x00,0x00,0x00,
		0x81,0x00,0x00,0x00,
		0x81,0x00,0x00,0x00
	}
};

uint8_t L1[4][9] = {
	{
		0x00,0x00,0x00,//L型1
		0x82,0x82,0x82,
		0x82,0x00,0x00,
	},{
		0x82,0x82,0x00,//L型1
		0x00,0x82,0x00,
		0x00,0x82,0x00,
	},{
		0x00,0x00,0x00,//L型1
		0x00,0x00,0x82,
		0x82,0x82,0x82,
	},{
		0x82,0x00,0x00,//L型1
		0x82,0x00,0x00,
		0x82,0x82,0x00,
	}

};

uint8_t L2[4][9] = {
	{
		0x00,0x00,0x00,//L型2
		0x83,0x00,0x00,
		0x83,0x83,0x83,
	},{
		0x83,0x83,0x00,//L型2
		0x83,0x00,0x00,
		0x83,0x00,0x00,
	},{
		0x00,0x00,0x00,//L型2
		0x83,0x83,0x83,
		0x00,0x00,0x83,
	},{
		0x00,0x83,0x00,//L型2
		0x00,0x83,0x00,
		0x83,0x83,0x00,
	}

};



uint8_t slip1[2][9] = {
	{
		0x00,0x84,0x00,//ずれ1
		0x84,0x84,0x00,
		0x84,0x00,0x00,
	},{
		0x00,0x00,0x00,//ずれ1
		0x84,0x84,0x00,
		0x00,0x84,0x84,
	}
};

uint8_t slip2[2][9] = {
	{
		0x85,0x00,0x00,//ずれ2
		0x85,0x85,0x00,
		0x00,0x85,0x00,
	},{
		0x00,0x00,0x00,//ずれ2
		0x00,0x85,0x85,
		0x85,0x85,0x00,
	}
};

uint8_t convex[4][9] = {
	{
		0x00,0x00,0x00,//凸型2
		0x86,0x86,0x86,
		0x00,0x86,0x00,
	},{
		0x00,0x86,0x00,//凸型2
		0x86,0x86,0x00,
		0x00,0x86,0x00,
	},{
		0x00,0x00,0x00,//凸型2
		0x00,0x86,0x00,
		0x86,0x86,0x86,
	},{
		0x86,0x00,0x00,//凸型2
		0x86,0x86,0x00,
		0x86,0x00,0x00,
	}
};

void playTetris(){
	static int tetrisState = 0;
	static int cnt = 0;

	if(tetrisState == 0){
		newBlock();
		tetrisState++;
	}else if(tetrisState <= 10){
		if(downButton()){
			if(fallBlock()) tetrisState++;
			else tetrisState = 1;
		}

		cnt++;
		if(cnt >= 10){
			if(fallBlock()) tetrisState++;
			else tetrisState = 1;
			cnt = 0;
		}

		if(leftButton()) leftBlock();
		if(rightButton()) rightBlock();
		if(upButton()) turnBlock();

	}else {
		fixedBlock();
		tetrisState = 0;
	}
	if(deleteLine()) tetrisState = 10;
	else if(tetrisState == 10) tetrisState = 11;
	if(gameOver()){
		for(int j = 0;j < 10;j++){
			for(int i = 0;i < 24;i++){
				bord[i][j] = 0x00;

			}
		}
	}
	displayBoard();
	HAL_Delay(50);
}

void displayBoard(){
	for(int i = 0;i < 20;i++){
		for(int j = 0;j < 10;j++){
			if((bord[i][j] & 0x7F) == 0x01) monitor[i][j] = 0x02;
			else if((bord[i][j] & 0x7F) == 0x02) monitor[i][j] = 0x0C;
			else if((bord[i][j] & 0x7F) == 0x03) monitor[i][j] = 0x20;
			else if((bord[i][j] & 0x7F) == 0x04) monitor[i][j] = 0x05;
			else if((bord[i][j] & 0x7F) == 0x05) monitor[i][j] = 0x11;
			else if((bord[i][j] & 0x7F) == 0x06) monitor[i][j] = 0x14;
			else if((bord[i][j] & 0x7F)) monitor[i][j] = 0x15;
			else monitor[i][j] = 0x00;
		}
	}
}

void newBlock(){
	int blockNum = rand() % 7;
	int cnt = 0;
	for(int i = 23;i >= 20;i--){

		for(int j = 2;j < 6;j++){
			bord[i][j] = block[blockNum][cnt];
			cnt++;
		}
	}
}

int getBottom(){
	for(int i = 0;i < 24;i++){
		for(int j = 0;j < 10;j++){
			if(bord[i][j] & 0x80){//移動中のブロック
				return i;
			}
		}
	}
	return 0;
}

int getLeft(){
	for(int j = 0;j < 10;j++){
		for(int i = 0;i < 24;i++){
			if(bord[i][j] & 0x80){//移動中のブロック
				return j;
			}
		}
	}
	return 0;
}

int getRight(){
	for(int j = 9;j >= 0;j--){
		for(int i = 0;i < 24;i++){
			if(bord[i][j] & 0x80){//移動中のブロック
				return j;
			}
		}
	}
	return 0;
}

int fallBlock(){
	int bottom = getBottom();
	int left = getLeft();

	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			if(bottom > 0){//一番下に来ていないとき
				if(bord[bottom + i][left + j] & 0x80){//移動中のピースであるとき
					uint8_t pieceState = bord[bottom - 1 + i][left + j];
					if(((pieceState & 0x80) == 0) && (pieceState & 0x7F)){//ピースの下に移動中で無いピースが存在した場合
						return 1;//移動できない
					}
				}
			}else return 1;//一番下だから移動不可
		}
	}
	//障害物が無い時
	for(int i = 0;i < 24;i++){
		for(int j = 0;j < 10;j++){
			if(bord[i][j] & 0x80){//移動中のピース
				bord[i - 1][j] = bord[i][j];//1つ下に移動
				bord[i][j] = 0x00;
			}
		}
	}
	return 0;
}

int leftBlock(){
	int bottom = getBottom();
	int left = getLeft();

	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			if(left > 0){//一番左に来ていないとき
				if(bord[bottom + i][left + j] & 0x80){//移動中のピースであるとき
					uint8_t pieceState = bord[bottom + i][left - 1 + j];
					if(((pieceState & 0x80) == 0) && (pieceState & 0x7F)){//ピースの下に移動中で無いピースが存在した場合
						return 1;//移動できない
					}
				}
			}else return 1;//一番下だから移動不可
		}
	}
	//障害物が無い時
	for(int i = 0;i < 24;i++){
		for(int j = 0;j < 10;j++){
			if(bord[i][j] & 0x80){//移動中のピース
				bord[i][j - 1] = bord[i][j];//1つ下に移動
				bord[i][j] = 0x00;
			}
		}
	}
	return 0;
}

int rightBlock(){
	int bottom = getBottom();
	int left = getLeft();
	int right = getRight();

	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			if(right < 9){//一番左に来ていないとき
				if(bord[bottom + i][right - j] & 0x80){//移動中のピースであるとき
					uint8_t pieceState = bord[bottom + i][right + 1 - j];
					if(((pieceState & 0x80) == 0) && (pieceState & 0x7F)){//ピースの下に移動中で無いピースが存在した場合
						return 1;//移動できない
					}
				}
			}else return 1;//一番下だから移動不可
		}
	}
	//障害物が無い時
	for(int i = 0;i < 24;i++){
		for(int j = 9;j >= 0;j--){
			if(bord[i][j] & 0x80){//移動中のピース
				bord[i][j + 1] = bord[i][j];//1つ下に移動
				bord[i][j] = 0x00;
			}
		}
	}
	return 0;
}

void fixedBlock(){//ブロックを固定
	for(int i = 0;i < 24;i++){
		for(int j = 0;j < 10;j++){
			if(bord[i][j] & 0x80){
				bord[i][j] = (bord[i][j] & 0x7F);//最上位bitを消す
			}
		}
	}
}



void turnBlock(){
	int blockId = checkBlock();
	int bottom = getBottom();
	int left = getLeft();
	int notFlag = 0;
	uint8_t max_i = 3,max_j = 3,cnt = 0;
	static uint8_t changeBlock[6] = {};

	if(blockId == 1){
		max_i = 4;
		max_j = 4;
	}
	if(blockId <= 6 && blockId > 0){
		for(int i = max_i - 1;i >= 0;i--){
			for(int j = 0;j < max_j;j++){
				int line = bottom + i;
				int row = left + j;
				uint8_t pieceState = bord[line][row];

				if(line < 24 && row < 10){
					if(blockId == 1){
						if(blockVertical[changeBlock[0]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}else if(blockId == 2){
						if(L1[changeBlock[1]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}else if(blockId == 3){
						if(L2[changeBlock[2]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}else if(blockId == 4){
						if(slip1[changeBlock[3]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}else if(blockId == 5){
						if(slip2[changeBlock[4]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}else{
						if(convex[changeBlock[5]][cnt] & 0x80){
							if(((pieceState & 0x80) == 0) && (pieceState & 0x7F))notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
						}
					}
					cnt++;
				}else notFlag = 1;//回転できない(回転するとそこに固定のブロックがある)
			}
		}

		cnt = 0;
		//kaiten Dosa
		if(notFlag == 0){
			for(int i = max_i - 1;i >= 0;i--){
				for(int j = 0;j < max_j;j++){
					int line = bottom + i;
					int row = left + j;
					uint8_t temp = 0;
					if(blockId == 1) temp = blockVertical[changeBlock[0]][cnt];
					else if(blockId == 2) temp = L1[changeBlock[1]][cnt];
					else if(blockId == 3) temp = L2[changeBlock[2]][cnt];
					else if(blockId == 4) temp = slip1[changeBlock[3]][cnt];
					else if(blockId == 5) temp = slip2[changeBlock[4]][cnt];
					else temp = convex[changeBlock[5]][cnt];

					if(temp || (bord[line][row] & 0x80)) bord[line][row] = temp;
					cnt++;
				}
			}

			for(int i = 0;i < 6;i++){//現在状態
				changeBlock[i] += 1;
				if((i == 1 || i == 2 || i == 5) && changeBlock[i] == 4) changeBlock[i] = 0;
				else if((i == 0 || i == 3 || i == 4) && changeBlock[i] == 2)changeBlock[i] = 0;
			}
		}

	}
}

int checkBlock(){
	int bottom = getBottom();
	int left = getLeft();
	for(int i = 0;i < 4;i++){
		for(int j = 0;j < 4;j++){
			int line = bottom + i;
			int row = left + j;
			if(line < 24 && row < 10){
				if(bord[line][row] & 0x80){
					int blockNum = bord[line][row] & 0x7F;
					return blockNum;
				}
			}
		}
	}
	return 0;
}

int deleteLine(){
	static uint8_t deleteNumber = 0;
	static uint8_t cache[10] = {};
	static uint8_t deleteCount = 0;
	if(deleteNumber){
		deleteCount++;
		if(deleteCount < 5) {
			for(int j = 0;j < 10;j++) bord[deleteNumber - 1][j] = 0;
		}else if(deleteCount < 10){
			for(int j = 0;j < 10;j++) bord[deleteNumber - 1][j] = cache[j];
		}else if(deleteCount < 15) {
			for(int j = 0;j < 10;j++) bord[deleteNumber - 1][j] = 0;
		}else if(deleteCount < 20){
			for(int j = 0;j < 10;j++) bord[deleteNumber - 1][j] = cache[j];
		}else if(deleteCount < 25) {
			for(int k= deleteNumber - 1;k < 22;k++){
				for(int j = 0;j < 10;j++) {
					bord[k][j] = bord[k + 1][j];//上の行を下ろしてくる
				}
			}
			for(int j = 0;j < 10;j++)bord[22][j] = 0;
			deleteCount = 0;
			deleteNumber = 0;
		}
		return 1;
	}else{
		for(int i = 0;i < 24;i++){
			int deleatBord = 0;
			for(int j = 0;j < 10;j++){
				if(((bord[i][j] & 0x80) == 0) && (bord[i][j] & 0x7F)){
					deleatBord++;
				}
			}
			if(deleatBord >= 10){// 消すとき
				for(int j = 0;j < 10;j++){
					cache[j] = bord[i][j];
				}
				deleteNumber = i + 1;
				return 1;
			}
		}
	}
	return 0;
}

int gameOver(){
	for(int i = 21;i < 24;i++){
		for(int j = 0;j < 10;j++){
			if(((bord[i][j] & 0x80) == 0) && (bord[i][j] & 0x7F)){
				return 1;
			}
		}
	}
	return 0;
}
