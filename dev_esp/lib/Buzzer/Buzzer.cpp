/******************************************************************************/
/*        @TITLE : Buzzer.cpp                                                 */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 07, 2017                                               */
/* @MODIFICATION : jan 07, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "Buzzer.h"



Buzzer::Buzzer() {
    channel.channel    = BUZZER_CHANNEL;
    channel.duty       = 0;
    channel.gpio_num   = BUZZER_GPIO;
    channel.speed_mode = BUZZER_MODE;
    channel.timer_sel  = BUZZER_TIMER;
    ledc_channel_config(&channel);
}


void Buzzer::set_frequency(uint16_t frequency) {
	ledc_timer_config_t buzzer_timer;
	buzzer_timer.duty_resolution = LEDC_TIMER_10_BIT,
	buzzer_timer.freq_hz = frequency,
	buzzer_timer.speed_mode = BUZZER_MODE;
	buzzer_timer.timer_num = BUZZER_TIMER;
    ledc_timer_config(&buzzer_timer);

}

void Buzzer::set_duty(uint16_t duty) {
	if (duty>1024) ledc_set_duty(channel.speed_mode, channel.channel, 1024);
	else ledc_set_duty(channel.speed_mode, channel.channel, duty);
	ledc_update_duty(channel.speed_mode, channel.channel);
}

void Buzzer::beep() {
	set_duty(1000);
	vTaskDelay(1000/portTICK_RATE_MS);
	set_duty(500);
	vTaskDelay(1000/portTICK_RATE_MS);
	set_duty(1000);
	vTaskDelay(1000/portTICK_RATE_MS);
	set_duty(0);
}
