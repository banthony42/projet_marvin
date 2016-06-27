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
    u8 non[2] = {45, 135};
    u8 oui[3] = {170, 90, 0};
    u8 mid[4] = {170, 90, 45, 0};
    u8 i3 = 0;
    u8 i2 = 0;
    u8 i1 = 0;
    while (1)
    {   
        if (PR1 == TMR1)
        {
    //        marvin_move_servo_speed(&marvin.servo_scan, non[i2], 1, 10);


            
            marvin_move_servo_speed(&marvin.servo_pitch, oui[i1], 1, 10);
            marvin_move_servo_speed(&marvin.servo_yaw, non[i2], 1, 10);
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
            if (i1 == 3)
                i1 = 0;
            if (i3 == 4)
                i3 = 0;

            /*
               if (i3 > 180)
                i3 = 0;
            marvin_move_servo(&marvin.servo_pitch, i3 );
            i3 += 90;
             */
         

        }  
    }
    return (0);
}

