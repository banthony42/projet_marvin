#include <p32xxxx.h>
#include "timer.h"
#include "types.h"
#include "Servo.h"

/*
 * Fonction qui configure un servo
 * Param1 : Objet m_servo, a setup
 * Param2 : Adresse du REGISTRE OCxCON (OutputCompare)
 * Param3 : Duty_cycle minimum du servo (0deg) en microsecondes
 * Param4 : Duty_cycle maximum du servo (180deg) en microsecondes
 * Param5 : Timer choisit pour le module de l'OutputCompare
*/

void    marvin_attach_servo(m_servo *servo, u32 *pin, u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode)
{
    servo->pin = pin;   //stockage adresse registre OCxCON
    servo->ocrs = ocrs; //stockage adresse registre OCxRS
    servo->min = min;   //stockage min duty_cycle
    servo->max = max;   //stockage max duty_cycle
    servo->pos = -1;    //pos initial
    servo->periode = periode;
    servo->oc_timer = oc_timer;
    *pin = OC_OFF;
    *pin = 0 | OCM | oc_timer;          // configuration du registre: OC1 disabled, OC1 mode: PWM, OC1 use TIMER2
    marvin_moove_servo(servo, 0);
    *pin |=  OC_ON;                     // OC1 enabled
  
}

/*
 * Fonction qui place un servo sur l'angle passez en param
 * Param1 : Objet m_servo a moove
 * Param2 : Angle du servo voulu (0 a 180 deg)
*/

void    marvin_moove_servo(m_servo *servo, u8 angle)
{
    if (servo->pos == angle)
        return ;
    servo->pos = angle;
    if (servo->oc_timer == OC_TIMER2)
    {
        *(servo->ocrs) = (PR2 * (servo->min + (angle * ((servo->max  - servo->min ) / 180)))) / servo->periode;     // Ecriture du nouveau duty_cycle dans le registre OCxRS
       //    *(servo->ocrs) =  servo->min + (angle * ((servo->max  - servo->min ) / 180));
    }
    else
        *(servo->ocrs) = (PR3 * (servo->min + (angle * ((servo->max - servo->min) / 180)))) / servo->periode;
                                                        
}