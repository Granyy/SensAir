/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "driver/ledc.h"
#include <iostream>
#include "Configuration.h"

using namespace std;


#define BLINK_GPIO GPIO_NUM_5 



extern "C" {
   void app_main();
}

class Color {
    public:
        uint8_t red;
        uint8_t blue;
        uint8_t green;
        Color(uint8_t _red, uint8_t _green, uint8_t _blue) {
            red = _red;
            blue = _blue;
            green = _green;
        }
        void set_color(uint8_t _red, uint8_t _green, uint8_t _blue) {
            red = _red;
            blue = _blue;
            green = _green;
        }
};

class LedRGB {
    public:
        LedRGB();
        void set_color(Color _color){*color = _color;};
        void fade_down(int time_ms);
        void fade_up(int time_ms);
        void fade_up_down(int time_ms);
        void fade_down_up(int time_ms);
        void set_off();
        void change_color(int time_ms, Color _color);
        void set_brightness(int _brightness){brightness = _brightness;};
    private:
        Color *color;
        int brightness;
        ledc_channel_config_t channelRed;
        ledc_channel_config_t channelGreen;
        ledc_channel_config_t channelBlue;
};



LedRGB::LedRGB() {
    color = new Color(0,0,0);
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

void LedRGB::fade_down_up(int time_ms) {
    fade_down(time_ms);
    fade_up(time_ms);
}

void LedRGB::fade_up_down(int time_ms) {
    fade_up(time_ms);
    fade_down(time_ms);
}

void LedRGB::fade_up(int time_ms) {
    ledc_set_fade_with_time(channelRed.speed_mode, channelRed.channel, (uint16_t)((float)(color->red/255)*brightness), time_ms);
    ledc_fade_start(channelRed.speed_mode, channelRed.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelGreen.speed_mode, channelGreen.channel, (uint16_t)((float)(color->green/255)*brightness), time_ms);
    ledc_fade_start(channelGreen.speed_mode, channelGreen.channel, LEDC_FADE_NO_WAIT);
    ledc_set_fade_with_time(channelBlue.speed_mode, channelBlue.channel, (uint16_t)((float)(color->blue/255)*brightness), time_ms);
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

void LedRGB::change_color(int time_ms, Color _color) {
    fade_down(time_ms);
    set_color(_color);
    fade_up(time_ms);
}


void app_main()
{
    Timer_config();
    Color white(255,255,255);
    Color green(0,255,0);
    Color red(255,0,0);
    Color blue(0,0,255);
    LedRGB ledRGB;
    
    while(1) {
        ledRGB.change_color(1000, green);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, red);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
        ledRGB.change_color(1000, blue);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}
