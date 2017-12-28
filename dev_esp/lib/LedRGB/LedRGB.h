/******************************************************************************/
/*        @TITLE : LedRGB.h                                                   */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : dec 28, 2017                                               */
/* @MODIFICATION : dec 28, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#ifndef __LEDRGB_H__

#define __LEDRGB_H__

#include "driver/ledc.h"
#include "Configuration.h"

#define BLACK 0,0,0
#define RED   255,0,0
#define GREEN 0,255,0
#define BLUE  0,0,255


class LedRGB {
    public:
        LedRGB();
        void set_color(uint8_t _red, uint8_t _green, uint8_t _blue);
        void fade_down(int time_ms);
        void fade_up(int time_ms);
        void fade_up_down(int time_ms);
        void fade_down_up(int time_ms);
        void set_off();
        void change_color(int time_ms, uint8_t _red, uint8_t _green, uint8_t _blue);
        void set_brightness(int _brightness){brightness = _brightness;};
    private:
        uint8_t red;
        uint8_t blue;
        uint8_t green;
        int brightness;
        ledc_channel_config_t channelRed;
        ledc_channel_config_t channelGreen;
        ledc_channel_config_t channelBlue;
};



#endif
