/******************************************************************************/
/*        @TITLE : StandAloneTreatment.cpp                                    */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "StandAloneTreatment.h"


uint8_t get_average(struct gas _gasValue) {
	uint8_t gasAverage=0;
	gasAverage = ((_gasValue.CO+_gasValue.CO2+_gasValue.NO2+_gasValue.VOC)/3);
	return gasAverage;
}


void change_color_from_average(uint8_t gasAverage, LedRGB ledRGB) {
			if (gasAverage<GREEN_TH) ledRGB.change_color(500,0,255,0);
			else if (gasAverage<YELLOW_TH) ledRGB.change_color(500, (int)((gasAverage-GREEN_TH)*255)/(YELLOW_TH-GREEN_TH), 255, 0);
			else if (gasAverage<RED_TH) ledRGB.change_color(500, 255, (int)((RED_TH - gasAverage)*255)/(RED_TH - YELLOW_TH), 0);
			else ledRGB.change_color(1000, 255,0,0);
}

void display_color(struct gas _gasValue, LedRGB ledRGB) {
			ledRGB.change_color(500,BLUE);
			ledRGB.change_color(500,SKY);
			ledRGB.change_color(500,PURPLE);
			uint8_t gasAverage= get_average(_gasValue);
			cout << "Average: " << (int)gasAverage << endl;
			change_color_from_average(gasAverage, ledRGB);
			vTaskDelay(5000/portTICK_RATE_MS);
			ledRGB.fade_down(1000);
}