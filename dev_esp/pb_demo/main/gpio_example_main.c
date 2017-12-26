#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/semphr.h"

#define GPIO_INPUT_IO_0     4
#define GPIO_INPUT_PIN_SEL  (1<<GPIO_INPUT_IO_0)
#define ESP_INTR_FLAG_DEFAULT 0

#define LEDC_LS_TIMER          LEDC_TIMER_1
#define LEDC_LS_MODE           LEDC_LOW_SPEED_MODE
#define LEDC_LS_CH3_GPIO       (5)
#define LEDC_LS_CH3_CHANNEL    LEDC_CHANNEL_3

#define LEDC_TEST_DUTY         (4000)
#define LEDC_TEST_FADE_TIME    (2000)


SemaphoreHandle_t xSemaphore = NULL;
	ledc_channel_config_t ledc_channel = 
	{
		.channel    = LEDC_LS_CH3_CHANNEL,
		.duty       = 0,
		.gpio_num   = LEDC_LS_CH3_GPIO,
		.speed_mode = LEDC_LS_MODE,
		.timer_sel  = LEDC_LS_TIMER
	};


static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
	xSemaphoreGiveFromISR(xSemaphore, NULL);
}

void button_task(void* arg) {
  for(;;) {
    if(xSemaphoreTake(xSemaphore,portMAX_DELAY) == pdTRUE) {
		printf("Button pressed!\n");
		ledc_set_fade_with_time(ledc_channel.speed_mode, ledc_channel.channel, LEDC_TEST_DUTY, LEDC_TEST_FADE_TIME);
		ledc_fade_start(ledc_channel.speed_mode, ledc_channel.channel, LEDC_FADE_NO_WAIT);
		vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);
		ledc_set_fade_with_time(ledc_channel.speed_mode, ledc_channel.channel, 0, LEDC_TEST_FADE_TIME);
		ledc_fade_start(ledc_channel.speed_mode, ledc_channel.channel, LEDC_FADE_NO_WAIT);
		vTaskDelay(LEDC_TEST_FADE_TIME / portTICK_PERIOD_MS);
    }
  }
}



void app_main()
{
	
    ledc_timer_config_t ledc_timer = {
        .bit_num = LEDC_TIMER_13_BIT, // resolution of PWM duty
        .freq_hz = 5000,              // frequency of PWM signal
        .speed_mode = LEDC_LS_MODE,   // timer mode
        .timer_num = LEDC_LS_TIMER    // timer index
    };
    ledc_timer_config(&ledc_timer);
	ledc_channel_config(&ledc_channel);
	ledc_fade_func_install(0);

	xSemaphore = xSemaphoreCreateBinary();
	
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_PIN_INTR_POSEDGE);


    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(GPIO_INPUT_IO_0, gpio_isr_handler, (void*) GPIO_INPUT_IO_0);

	xTaskCreate(&button_task, "button_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}

