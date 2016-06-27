#include <p32xxxx.h>
#include "timer.h"
#include "types.h"
#include "leds.h"
#include <p32xxxx.h>

/*
 * Fonction qui configure une led
 * Param1 : Objet m_led, a setup
 * Param2 : Adresse du REGISTRE OCxCON (OutputCompare) correspondant a la PIN OC choisit
 * Param3 : Duty_cycle minimum de la led
 * Param4 : Duty_cycle maximum du la led
 * Param5 : Timer choisit pour le module de l'OutputCompare
 * Param6 : Periode du signal PWM pour cet objet Led
 */
void    marvin_attach_led(m_led *led, u32 *pin, u32 *ocrs, u16 min, u16 max, u8 oc_timer, u16 periode)
{
    led->pin = pin;             //stockage adresse registre OCxCON
    led->ocrs = ocrs;           //stockage adresse registre OCxRS
    led->min = min;             //stockage min duty_cycle
    led->max = max;             //stockage max duty_cycle
    led->lux = -1;              //pos initial
    led->periode = periode;     //stockage periode
    led->oc_timer = oc_timer;   //stockage timer
    *pin = OC_OFF;              //Registre disable le temps de la config
    *pin = 0 | OCM | oc_timer;  // configuration du registre: OC1 disabled, OC1 mode: PWM, OC1 use TIMER2
    *pin |=  OC_ON;             // OC1 enabled
    marvin_set_lux(led, 0);     // init position a 0 degres
    _nop();
}

/*
 * Fonction qui allume une led fonction de la luminosite passer en parametre
 * Param1 : Objet m_led a allumer
 * Param2 : Luminosite voulue (0 a 100)
 */
void    marvin_set_lux(m_led *led, s16 lux)
{
    if (led->lux == lux || lux > 100 || lux < 0)                                                    // Gestion d'erreur
        return ;
    led->lux = lux;                                                                                 // Enregistrement de la nouvelle luminosite
    if (led->oc_timer == OC_TIMER2)
          *(led->ocrs) = (PR2 * (led->min + (lux * ((led->max - led->min) / 100)))) / led->periode;
    else
         *(led->ocrs) = (PR3 * (led->min + (lux * ((led->max - led->min) / 100)))) / led->periode;   // Ecriture du nouveau duty_cycle dans le registre OCxRS, cas du TIMER3
}

void    marvin_set_lux_speed(m_led *led, s16 lux, u16 deg_per_periode, u16 periode_msec)
{
    if (led->lux == lux || lux > 100 || lux < 0)                                    // Gestion d'erreur, angle impossible, ou servo deja en position
        return ;
    led->new_lux = lux;
    led->vitesse = periode_msec;
    if (lux > led->lux)                                                                // Determination de l'operation a effectuer pour l'increment, (addition ou soustraction)
        led->incr = 1 * deg_per_periode;
    else
        led->incr = -1 * deg_per_periode;
}