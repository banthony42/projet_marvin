
#include "timer.h"
#include "types.h"
#include <p32xxxx.h>
/*
 * Fonction qui set le TIMER
 * Param1 : Registre du Timer a set MARVIN_CONF_TIMERx
 * Param2 : Le prescaler du timer (entre 0b0 et 0b111)TCKPSx
 * Param3 Tgate a 0 ou 1 -> 0 c'est mieux TIMER_GATE_ON et TIMER_GATE_OFF
 * Param4 : Le timer pour le foutre a zero MARVIN_TIMERx
*/


void    marvin_set_timer(u32 *stimer, u8 prescale, u8 gate, u32 timer)
{
    *stimer = 0 | TIMER_ON | prescale | gate;
    timer = 0;
}

/*
 * Definie la periode du Timer voulue en secondes
 * Param1 : Le registre du reset du timer voulue
 * Param2 : La periode voulue en secondes(max 255)
 * Param3 : Type du timer : 1 -> type A; 0 -> type B;
 */

void    marvin_set_reset_timer_s(u32 timer, u8 periode, u8 types)
{

}

