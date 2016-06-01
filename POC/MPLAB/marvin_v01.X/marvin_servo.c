
#include "timer.h"
#include "types.h"
#include "Servo.h"
#include <p32xxxx.h>

/*
 * Fonction qui configure un servo
 * Param1 : Objet m_servo, a setup
 * Param2 : Adresse du REGISTRE OCxCON (OutputCompare)
 * Param3 : Duty_cycle minimum du servo (0deg)
 * Param4 : Duty_cycle maximum du servo (180deg)
 * Param5 : Timer choisit pour le module de l'OutputCompare
*/

void    marvin_attach_servo(m_servo *servo, u32 *pin, u32 *ocrs, u8 min, u8 max, u8 oc_timer)
{
    servo->pin = pin;   //stockage adresse registre OCxCON
    servo->ocrs = ocrs; //stockage adresse registre OCxRS
    servo->min = min;   //stockage min duty_cycle
    servo->max = max;   //stockage max duty_cycle
    servo->pos = 90;    //pos initial
    *pin = 0 | OC_OFF | OCM | oc_timer;   // configuration du registre: OC1 disabled, OC1 mode: PWM, OC1 use TIMER2
    *ocrs = 1500;                         // Init du duty_cycle a 1.5 ms = pos initial
    *pin = *pin | OC_ON;            // OC1 enabled
}


/*
 * Fonction qui place un servo sur l'angle passez en param
 * Param1 : Objet m_servo a moove
 * Param2 : Angle du servo voulu (0 a 180 deg)
*/

void    marvin_moove_servo(m_servo *servo, u8 angle)
{
    u8 mult = 0;
    u32 *ocrs;

    ocrs = servo->pin;
    if (angle == servo->pos || angle > 180 || angle < 0)    // Gestion erreur
        return;
    mult = (servo->max - servo->min) / 180;                 // Calcul du multiplicateur
    *ocrs = angle * mult;                             // Ecriture du nouveau duty_cycle dans le registre OCxRS
}