/******************************************************************************/
/*        @TITLE : LedRGB.cpp                                                 */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 28, 2017                                               */
/* @MODIFICATION : dec 28, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#include "LedRGB.h"



LedRGB::LedRGB() {
    set_color(0,0,0);
    brightness = 1000;

    channelRed.channel    = LEDR_CHANNEL;
    channelRed.duty       = 0;
    channelRed.gpio_num   = LEDR_GPIO;
    channelRed.speed_mode = LEDRGB_MODE;
    channelRed.timer_sel  = LEDRGB_TIMER;
    ledc_channel_config(&channelRed);
    channelGreen.channel    = LEDG_CHANNEL;
    channelGreen.duty       = 0;
    channelGreen.gpio_num   = LEDG_GPIO;
    channelGreen.speed_mode = LEDRGB_MODE;
    channelGreen.timer_sel  = LEDRGB_TIMER;
    ledc_channel_config(&channelGreen);
    channelBlue.channel    = LEDB_CHANNEL;
    channelBlue.duty       = 0;
    channelBlue.gpio_num   = LEDB_GPIO;
    channelBlue.speed_mode = LEDRGB_MODE;
    channelBlue.timer_sel  = LEDRGB_TIMER;
    ledc_channel_config(&channelBlue);
}

void LedRGB::set_color(uint8_t _red, uint8_t _green, uint8_t _blue) {
            red = _red;
            blue = _blue;
            green = _green;
}

void LedRGB::fade_down_up(int time_ms) {
    fade_down(time_ms);
    fade_up(time_ms);
}

void LedRGB::fade_up_down(int time_ms) {
    fade_up(time_ms);
    fade_down(time_ms);
}

void LedRGB::fade_up(int time_ms) {
    ledc_set_fade_with_time(channelRed.speed_mode, channelRed.channel, (uint16_t)((float)(red/255)*brightness), time_ms);
    ledc_fade_start(channelRed.speed_mode, channelRed.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelGreen.speed_mode, channelGreen.channel, (uint16_t)((float)(green/255)*brightness), time_ms);
    ledc_fade_start(channelGreen.speed_mode, channelGreen.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelBlue.speed_mode, channelBlue.channel, (uint16_t)((float)(blue/255)*brightness), time_ms);
    ledc_fade_start(channelBlue.speed_mode, channelBlue.channel, LEDC_FADE_NO_WAIT);
	vTaskDelay((time_ms+100) / portTICK_PERIOD_MS);

}

void LedRGB::fade_down(int time_ms) {
    ledc_set_fade_with_time(channelRed.speed_mode, channelRed.channel, 0, time_ms);
    ledc_fade_start(channelRed.speed_mode, channelRed.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelGreen.speed_mode, channelGreen.channel, 0, time_ms);
    ledc_fade_start(channelGreen.speed_mode, channelGreen.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelBlue.speed_mode, channelBlue.channel, 0, time_ms);
    ledc_fade_start(channelBlue.speed_mode, channelBlue.channel, LEDC_FADE_NO_WAIT);
	vTaskDelay((time_ms+100) / portTICK_PERIOD_MS);
    set_off();
}


void LedRGB::set_off() {
    ledc_set_duty(channelRed.speed_mode, channelRed.channel, 0);
	ledc_update_duty(channelRed.speed_mode, channelRed.channel);
    ledc_set_duty(channelGreen.speed_mode, channelGreen.channel, 0);
	ledc_update_duty(channelGreen.speed_mode, channelGreen.channel);
    ledc_set_duty(channelBlue.speed_mode, channelBlue.channel, 0);
	ledc_update_duty(channelBlue.speed_mode, channelBlue.channel);
}

void LedRGB::change_color(int time_ms, uint8_t _red, uint8_t _green, uint8_t _blue) {
    fade_down(time_ms);
    set_color(_red, _green, _blue);
    fade_up(time_ms);
}

