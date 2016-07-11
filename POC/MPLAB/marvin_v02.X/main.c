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

        /*
         * Useless
        if (TMR1 == PR1)
       {
            marvin_send_message("Je suis Marvin et j'ai la tete comme une planete", 50);
            TMR1 = 0;
       }
         */

/*  PB AVEC LE RELAIS ALIM TOUT LE TEMPS A 5V SUR SERVO
 *      INTGRATION CODE
 *  FONCTION TIMER => OK
 *  FONCTION SERVO => OK
 *  FONCTION SONAR => OK
 *  FONCTION IR    => OK
 *  FONCTION LEDS  => OK
 * 
 *  FAIRE FONCTIONNER L'UART a
 *
 *  SERVO PITCH DEBATTEMENT MAX: 50 a 100, repos a 60
 */

int main()
{
    marvin_setup(&marvin);
    marvin_init(&marvin);
    marvin.found = marvin.counter3;
    while (1)
    {
         marvin_refresh(&marvin);
        _nop();
        if (behavior.feel_alone && behavior.feel_spite != 2 && behavior.feel_sleepy != 2)
            marvin_look_around();   // Look around, toute les 20sec sans detection
        if (behavior.feel_spite == 2 && behavior.feel_sleepy != 2)
            marvin_spite();         // Spite, au bout de 2 Look around
        if (behavior.feel_sleepy == 2)
            marvin_veille(30000);   //Mode veille de 30sec, au bout de 2 Spite
        if (marvin_is_someone_found(marvin) && behavior.feel_sleepy < 2)
        {
            marvin_stop_move(&marvin);
            marvin_set_lux_speed(&marvin.led_left, 40, 1, 40);
            marvin_set_lux_speed(&marvin.led_right, 40, 1, 40);
            marvin_move_servo_speed(&marvin.servo_pitch, PITCH_MAX, 1, 25);
            if (marvin.found < marvin.counter3)
                marvin_send_message("5\n");         // Tell to the Pi, Track with my cam
            marvin.found = marvin.counter3;
         }
        else
            marvin_move_servo_speed(&marvin.servo_pitch, PITCH_REST, 1, 25);
        if (marvin_is_someone_left(marvin) && behavior.feel_sleepy < 2)
        {
           marvin_set_lux_speed(&marvin.led_right, 40, 1, 20);
           marvin_set_lux_speed(&marvin.led_left, 1, 1, 20);
           marvin_move_servo_speed(&marvin.servo_yaw, YAW_MAX, 1, 37);
           marvin_move_servo_speed(&marvin.servo_pitch, PITCH_REST, 1, 25);
        }
        if (marvin_is_someone_right(marvin) && behavior.feel_sleepy < 2)
        {
           marvin_set_lux_speed(&marvin.led_right, 1, 1, 20);
           marvin_set_lux_speed(&marvin.led_left, 40, 1, 20);
           marvin_move_servo_speed(&marvin.servo_yaw, YAW_MIN, 1, 37);
           marvin_move_servo_speed(&marvin.servo_pitch, PITCH_REST, 1, 25);
        }
    }
    return (0);
}


