/*
 * controcLed.cpp
 *
 *  Created on: Jul 16, 2019
 *      Author: naoki
 */

#include <controlLed.h>




void writeLED(){
	int k = 0;
	int k_flag = 0;//逆順の時は1
	for(int m = 0;m < 20 ; m++){
		for(int k2 = 0;k2 < 10 ; k2++){//横方向
			uint8_t temp_GRB[3] = {};
			temp_GRB[0] = (monitor[m][k] & 0x0C) * LED_LIGHT;
			temp_GRB[1] = (monitor[m][k] & 0x30) * LED_LIGHT;
			temp_GRB[2] = (monitor[m][k] & 0x03) * LED_LIGHT;
			uint8_t cnt = 0;
			for(int j=0;j < 3;j++){
				uint8_t temp = temp_GRB[j];
				for(int i=0;i < 4;i++){
					if(temp & 0x80) spi_data[(m  * 10 + k2) * 12 + cnt] = 0x10;//1 �?数bit
					else spi_data[(m  * 10 + k2) * 12 + cnt] = 0x70;//0
					if(temp & 0x40) spi_data[(m  * 10 + k2) * 12 + cnt] += 0x01;//1 偶数bit
					else spi_data[(m  * 10 + k2) * 12 + cnt] += 0x07;//0

					temp = temp << 2;//2bit上にずら�?
					cnt++;
				}
			}



			//折り返し処理
			if(k_flag)k--;
			else k++;
			if(k == 10){
				k_flag = 1;
				k = 9;//9の次も9
				break;
			}
			if(k == -1){
				k_flag = 0;
				k = 0;//0の次も0
				break;
			}

		}
	}



}

int leftButton(){
	static uint8_t state = 0;
	int button = HAL_GPIO_ReadPin(LEFT_GPIO_Port,LEFT_Pin);
	if(!state && button){
		state = 1;
		return 1;
	}
	if(state && !button) state = 0;

	return 0;
}

int rightButton(){
	static uint8_t state = 0;
	int button = HAL_GPIO_ReadPin(RIGHT_GPIO_Port,RIGHT_Pin);
	if(!state && button){
		state = 1;
		return 1;
	}
	if(state && !button) state = 0;

	return 0;
}

int upButton(){
	static uint8_t state = 0;
	int button = HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin);
	if(!state && button){
		state = 1;
		return 1;
	}
	if(state && !button) state = 0;

	return 0;
}

int downButton(){
	static uint8_t state = 0;
	int button = HAL_GPIO_ReadPin(DOWN_GPIO_Port,DOWN_Pin);
	if(!state && button){
		state = 1;
		return 1;
	}
	if(state && !button) state = 0;

	return 0;
}

