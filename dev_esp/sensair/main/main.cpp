#include <esp_log.h>
#include <iostream>
#include <string>
#include <Task.h>
#include <sys/time.h>
#include <sstream>
#include "sdkconfig.h"
#include <iostream>
#include "FreeRTOS.h"
#include <freertos/task.h>
#include "Configuration.h"
#include "gpio.h"
#include "GasTreatment.h"
#include "LedRGB.h"
#include <math.h>
#include "esp_attr.h"
#include "SensairBLE.h"


using namespace std;


extern "C" {
   void app_main();
}


SemaphoreHandle_t isrSemaphore = NULL;
int cnt = 0; //A PROTEGER AVEC SEMAPHORE

GasValue gasValueTEST;

void gas_task(void* arg) {
	GasTreatment gasTreatment;
	gasTreatment.begin();
	while (1) {
		gasTreatment.treat_gas();
		gasValueTEST.set_gasValue(gasTreatment.get_gasValue());
		gasValueTEST.set_gasRawValue(gasTreatment.get_gasRawValue());
		vTaskDelay(10000/portTICK_RATE_MS);
	}
}

void IRAM_ATTR gpio_isr_handler(void* arg) {
	if (cnt == 0) {
		xSemaphoreGiveFromISR(isrSemaphore, NULL);
		cnt++;
	}
}

void stand_alone_task (void* arg) {
	uint8_t gasAverage=0;
	LedRGB ledRGB;
	struct gas _gasValue;
	 for(;;) {
	    if(xSemaphoreTake(isrSemaphore,portMAX_DELAY) == pdTRUE) {
	    	_gasValue = gasValueTEST.get_gasValue();
			ledRGB.change_color(500,BLUE);
			ledRGB.change_color(500,SKY);
			ledRGB.change_color(500,PURPLE);
			gasAverage = ((_gasValue.CO+_gasValue.CO2+_gasValue.NO2+_gasValue.VOC)/3);
			cout << "Average: " << (int)gasAverage << endl;
			if (gasAverage<GREEN_TH) ledRGB.change_color(500,0,255,0);
			else if (gasAverage<YELLOW_TH) ledRGB.change_color(1000, (int)((gasAverage-GREEN_TH)*255)/(YELLOW_TH-GREEN_TH), 255, 0);
			else if (gasAverage<RED_TH) ledRGB.change_color(1000, 255, (int)((RED_TH - gasAverage)*255)/(RED_TH - YELLOW_TH), 0);
			else ledRGB.change_color(1000, 255,0,0);
			vTaskDelay(5000/portTICK_RATE_MS);
			ledRGB.fade_down(1000);
			cnt = 0;
	    }
	  }

}

void run_server(void) {
	MainBLEServer* pMainBleServer = new MainBLEServer();
	pMainBleServer->setStackSize(20000);
	pMainBleServer->start(static_cast<void*>(&gasValueTEST));

}


void app_main(void)
{
	isrSemaphore = xSemaphoreCreateBinary();
	configure();
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);

	xTaskCreate(&gas_task, "gas_task", 2048, NULL, 5, NULL);
	xTaskCreate(&stand_alone_task, "stand_alone_task", 2048, NULL, 5, NULL);
	run_server();
}
