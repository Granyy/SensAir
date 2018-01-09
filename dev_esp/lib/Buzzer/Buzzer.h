/******************************************************************************/
/*        @TITLE : Buzzer.h                                                   */
/*      @VERSION : 1.0                                                        */
/*     @CREATION : jan 07, 2017                                               */
/* @MODIFICATION : jan 07, 2017                                               */
/*       @AUTHOR : Leo GRANIER                                                */
/******************************************************************************/

#ifndef __BUZZER_H__

#define __BUZZER_H__

#include "driver/ledc.h"
#include "Configuration.h"



class Buzzer {
    private:
        ledc_channel_config_t channel;
    public:
        Buzzer();
        void beep();
        void set_duty(uint16_t duty);
        void set_frequency(uint16_t frequency);
};



#endif
