
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


void    marvin_set_timer(u32 *stimer, u8 prescale, u8 gate, u32 *timer)
{
    *stimer = 0 | TIMER_ON | prescale | gate;
    *timer = 0;
}

/*
 * Definie la periode du Timer voulue en secondes
 * Param1 : Le registre du reset du timer voulue
 * Param2 : La periode voulue en secondes(max 255)
 * Param3 : Type du timer : 1 -> type A; 0 -> type B;
 * Param4 : Registre du Timer TxCON
 */

void    marvin_set_periode_s(u32 *pr_timer, u8 periode, u8 types, u32 *conf_tmr)
{
    /*
     * Stockage valeur des prescale oscillator et timer
     */
    u8 frcdiv = 0;
    u8 pbdiv = 0;
    u32 prescale = 0;
    u8 div = 1;

    frcdiv = OSCCONbits.FRCDIV;
    pbdiv = OSCCONbits.PBDIV;
    prescale = ((0b11 << 4) & *conf_tmr) >> 4;
}