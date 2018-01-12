/******************************************************************************/
/*        @TITLE : StandAloneTreatment.h                                      */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/



#ifndef __STANDALONETREATMENT_H__
#define __STANDALONETREATMENT_H__

#include <string>
#include <iostream>
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "GasValue.h"
#include "LedRGB.h"

#define GREEN_TH 20
#define YELLOW_TH 50
#define RED_TH 80


using namespace std;


uint8_t get_average(struct gas _gasValue);
void change_color_from_average(uint8_t gasAverage, LedRGB ledRGB);
void display_color(struct gas _gasValue, LedRGB ledRGB, bool error);


#endif
