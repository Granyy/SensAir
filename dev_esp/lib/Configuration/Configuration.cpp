/******************************************************************************/
/*        @TITLE : Configuration.c                                            */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 27, 2017                                               */
/* @MODIFICATION : dec 27, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "Configuration.h"


void configure() {
	ISR_config();
	I2C_config();
	Timer_config();
	Led_config();
	ADC_config();
}

void I2C_config() {
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = (gpio_num_t)I2C_SDA_PIN;
	conf.scl_io_num = (gpio_num_t)I2C_SCL_PIN;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = I2C_SPEED;
	i2c_param_config(I2C_INTERFACE, &conf);
	i2c_driver_install(I2C_INTERFACE, I2C_MODE_MASTER, 0, 0, 0);
}


void Timer_config() {
	ledc_timer_config_t ledc_timer;
	ledc_timer.duty_resolution = LEDC_TIMER_10_BIT,
	ledc_timer.freq_hz = LEDRGB_FREQ,
	ledc_timer.speed_mode = LEDRGB_MODE;
	ledc_timer.timer_num = LEDRGB_TIMER;
    ledc_timer_config(&ledc_timer);

	ledc_timer_config_t buzzer_timer;
	buzzer_timer.duty_resolution = LEDC_TIMER_10_BIT,
	buzzer_timer.freq_hz = BUZZER_FREQ,
	buzzer_timer.speed_mode = BUZZER_MODE;
	buzzer_timer.timer_num = BUZZER_TIMER;
    ledc_timer_config(&buzzer_timer);
}

void Led_config() {
    gpio_pad_select_gpio(PWR_LED_GPIO);
    gpio_set_direction(PWR_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(PWR_LED_GPIO, 1);

    gpio_pad_select_gpio(BLE_LED_GPIO);
    gpio_set_direction(BLE_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(BLE_LED_GPIO, 0);
}

void ADC_config() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_0);
}


void ISR_config() {
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en =  GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_POSEDGE);
    gpio_install_isr_service(0);
}
