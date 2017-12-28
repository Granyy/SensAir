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
        ledRGB.change_color(1000, GREEN);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, RED);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, BLUE);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}
