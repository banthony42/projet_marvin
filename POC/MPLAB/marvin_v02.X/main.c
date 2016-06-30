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
 *  FONCTION LEDS  => OK
 * 
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
    marvin_init(&marvin);

    while (1)
    {
        if (TMR1 == PR1)
       {
            marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
            TMR1 = 0;
       }
       /*     if (marvin.counter1 > 60000)
       //         marvin_veille(60000);
       //     else
       //     {
/*                marvin_refresh(&marvin);
                if (marvin_is_someone_found(marvin))
                {
                    marvin_stop_move(&marvin);
                    marvin_set_lux_speed(&marvin.led_left, 0, 1, 40);
                    marvin_set_lux_speed(&marvin.led_right, 0, 1, 40);
                    marvin_send_message("found", 6);
                 }
                if (marvin_is_someone_left(marvin))
                {
                     marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos +10, 1, 25);
                     marvin_set_lux_speed(&marvin.led_left, 20, 1, 40);
                     marvin_send_message("yolo", 5);
                }
                if (marvin_is_someone_right(marvin))
                {
                     marvin_move_servo_speed(&marvin.servo_yaw, marvin.servo_yaw.pos - 10, 1, 25);
                     marvin_set_lux_speed(&marvin.led_right, 20, 1, 40);
                  //   marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
                }
//            }*/
    }
    return (0);
}

