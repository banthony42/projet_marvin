
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
 * Definie la periode du Timer voulue en secondes, on utilise l'osc interne
 * Param1 : Le registre du reset du timer voulue
 * Param2 : La periode voulue en secondes(max 255)
 * Param3 : Type du timer : 1 -> type A; 0 -> type B;
 * Param4 : Registre du Timer TxCON
 */
// faire une verif de OSCTUN pour voir si la clock est bien a 8 MHZ ???
void    marvin_set_periode_s(u32 *pr_timer, u8 periode, u8 types, u32 *conf_tmr)
{
    // il va falloir recuperer frcdiv -> puissance de 2

    ///u8 test = OSC_INTERNE >> 24 & 0b111;
    u16 frcdiv[8] = {0, 2, 4, 8, 16 , 32, 64, 456};
    u8 frc = OSC_INTERNE >> 12 & 0b111;
    u32 result;
    // test  pour savoir par quelle prescaler on passe / 16 , frdvi ou frc
    // Normalement on utilise pas les autres options
    if (frc == 0b111) // diviser par frcdiv
    {
         result = OCSINTERNE / frcdiv[OSC_INTERNE >> 24 & 0b111];
    }else if (frc == 0b110) // diviser par 16
    {
        result = OCSINTERNE / 16;
    }else if (frc == 0b000) // pas de diviosn
    {
        result = OCSINTERNE;
    }

    // division par PBCLK (PBDIV)

    result /= 1 << (OSC_INTERNE >> 19 & 0b11);
    //test si type A ou B -> pas le meme tableau

    asm volatile ("nop");




    /*
     * Stockage valeur des prescale oscillator et timer
     */
    /*
    u8 frcdiv = 0;
    u8 pbdiv = 0;
    u32 prescale = 0;
    u8 div = 1;

    frcdiv = OSCCONbits.FRCDIV;
    pbdiv = OSCCONbits.PBDIV;
    prescale = ((0b11 << 4) & *conf_tmr) >> 4;
     * */
}