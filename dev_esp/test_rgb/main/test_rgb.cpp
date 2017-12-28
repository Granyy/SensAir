#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <iostream>
#include "Configuration.h"
#include "LedRGB.h"

using namespace std;


extern "C" {
   void app_main();
}


void app_main()
{
    Timer_config();
    LedRGB ledRGB;
    
    while(1) {
        ledRGB.change_color(1000, 125, 255,0);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, 255, 255,0);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, 255, 125,0);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
		ledRGB.change_color(1000, 255,0,0);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}
