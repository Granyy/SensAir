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
#include "StandAloneTreatment.h"
#include "Buzzer.h"


using namespace std;


extern "C" {
   void app_main();
}


SemaphoreHandle_t isrSemaphore = NULL;
int cnt = 0; //A PROTEGER AVEC SEMAPHORE

GasValue gasValue;

void gas_task(void* arg) {
	GasTreatment gasTreatment;
	gasTreatment.begin();
	while (1) {
		gasTreatment.treat_gas();
		gasValue.set_gasValue(gasTreatment.get_gasValue());
		gasValue.set_gasRawValue(gasTreatment.get_gasRawValue());
		vTaskDelay(5000/portTICK_RATE_MS);
	}
}

void IRAM_ATTR gpio_isr_handler(void* arg) {
	if (cnt == 0) {
		xSemaphoreGiveFromISR(isrSemaphore, NULL);
		cnt++;
	}
}

void stand_alone_task (void* arg) {
	LedRGB ledRGB;
	struct gas _gasValue = {0,0,0,0};
	 for(;;) {
	    if(xSemaphoreTake(isrSemaphore,portMAX_DELAY) == pdTRUE) {
	    	_gasValue = gasValue.get_gasValue();
	    	display_color(_gasValue, ledRGB);
			cnt = 0;
	    }
	  }

}

void run_server(void) {
	MainBLEServer* pMainBleServer = new MainBLEServer();
	pMainBleServer->setStackSize(20000);
	pMainBleServer->start(static_cast<void*>(&gasValue));

}


void app_main(void)
{
	configure();
	isrSemaphore = xSemaphoreCreateBinary();
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);
	xTaskCreate(&gas_task, "gas_task", 4096, NULL, 5, NULL);
	xTaskCreate(&stand_alone_task, "stand_alone_task", 4096, NULL, 5, NULL);
	run_server();
}
