/* 
 * File:   main.c
 * Author: bocal
 *
 * Created on June 22, 2016, 6:34 PM
 */
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"
#include "timer.h"
#include "Servo.h"
#include "setup.h"
#include "marvin.h"

/*  PB AVEC LE RELAIS ALIM TOUT LE TEMPS A 5V SUR SERVO
 *      INTGRATION CODE
 *  FONCTION TIMER => OK
 *  FONCTION SERVO => OK
 *  FONCTION SONAR => OK
 *  FONCTION IR    => OK
 *
 *  FAIRE FCT LEDS
 *  FAIRE FONCTIONNER L'UART
 */

/*
void __ISR(_TIMER_1_VECTOR, IPL7) timer1_handler()
{
  marvin_timestamp.time += TIME_TMR1;
  IFS0bits.T1IF = 0; // Clear l'interrupt
}
*/


int main()
{
    marvin_setup(&marvin);
  
    LATBbits.LATB11 = 0;        // ALIM SENSOR, 1 = OFF , 0 = ON
    TRISBbits.TRISB11 = 0;
    u8 non[2] = {80, 100};
    u8 oui[8] = {0, 180, 20, 30, 40, 50, 60, 70};
    u8 mid[2] = {50, 0};
    u8 i3 = 0;
    u8 i2 = 0;
    u8 i1 = 0;
    while (1)
    {   
        if (PR1 == TMR1)
        {
            marvin_move_servo_speed(&marvin.servo_pitch, oui[i1], 1, 10);
            marvin_move_servo_speed(&marvin.servo_yaw, non[i2], 1, 10);
            marvin_set_lux_speed(&marvin.led_left, mid[i3], 1, 40);
            marvin_set_lux_speed(&marvin.led_right, mid[i3], 1, 40);
            marvin.val_sonar_r = marvin_capture(&marvin.sonar_right);
            marvin.val_sonar_l = marvin_capture(&marvin.sonar_left);
            marvin.val_ir = capture_ir(MARVIN_CONF_TIMER4, MARVIN_PR4, MARVIN_TIMER4);
            _nop();
            TMR1 = 0;
            i3++;
            i2++;
            i1++;
            if (i2 == 2)
                i2 = 0;
            if (i1 == 8)
                i1 = 0;
            if (i3 == 2)
                i3 = 0;
        }  
    }
    return (0);
}

