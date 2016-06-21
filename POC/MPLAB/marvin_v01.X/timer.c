
#include "timer.h"
#include "types.h"
#include <p32xxxx.h>
#include <sys/attribs.h>

/*
 * Fonction qui set le TIMER
 * Param1 : Registre du Timer a set MARVIN_CONF_TIMERx
 * Param2 : Le prescaler du timer (entre 0b0 et 0b111)TCKPSx
 * Param3 Tgate a 0 ou 1 -> 0 c'est mieux TIMER_GATE_ON et TIMER_GATE_OFF
 * Param4 : Le timer pour le foutre a zero MARVIN_TIMERx
 * Param5 : type a ou type b pour mettre le type B en 32 bits
 *
 * ATTENTION AUX OVERFLOW, BIEN CHOISIR LE TCKPS, CAR PRx EST SUR 16 BITS
*/
void    marvin_set_timer(u32 *stimer, u8 prescale, u8 gate, u32 *timer)
{
    *stimer = 0 | prescale | gate;
    *stimer |= TIMER_ON;
    *timer = 0;
}

/*
 * Fonction qui calcul la frequence en fonction des POSTSCALER
 */
u32     marvin_calcul_oscillator_prescaler()
{
    u32 result;
    u8 frc = OSC_INTERNE >> 12 & 0b111;
    u16 frcdiv[8] = {1, 2, 4, 8, 16 , 32, 64, 256}; // sert pour le type B aussi

    if (frc == 0b111)                               // diviser par frcdiv
        result = OCSINTERNE / frcdiv[(OSC_INTERNE >> 24) & 0b111];
    else if (frc == 0b110)                          // diviser par 16
        result = OCSINTERNE / 16;
    else if (frc == 0b000)                          // pas de diviosn
        result = OCSINTERNE;
    result /= 1 << ((OSC_INTERNE >> 19) & 0b11);    // division par PBCLK (PBDIV)
}

/*
 * Definie la periode du Timer voulue en secondes, en fonction de la valeurs des postscaler et prescaler
 * Param1 : Le registre du reset du timer voulue
 * Param2 : La periode voulue en secondes(max 255)
 * Param3 : Type du timer : 1 -> type A; 0 -> type B;
 * Param4 : Registre du Timer TxCON
 * Param5 : Unite de la periode voulu (secondes, milisecondes, microsecondes)
 *
 * Faire une verif de OSCTUN pour voir si la clock est bien a 8 MHZ ?
 */
void    marvin_set_periode(u32 *pr_timer, u16 periode, u8 types, u32 *conf_tmr, u16 unit)
{
    // il va falloir recuperer frcdiv -> puissance de 2
    u16 frcdiv[8] = {1, 2, 4, 8, 16 , 32, 64, 256}; // sert pour le type B aussi
    u32 result;
    u16 typeA[4] = {1, 8, 64, 256};

    result = marvin_calcul_oscillator_prescaler();
    if (types == TYPE_A)                            //test si type A ou B -> pas le meme tableau
        result /= typeA[(*conf_tmr >> 4) & 0b11];
    else
        result /= frcdiv[(*conf_tmr >> 4) & 0b111];
    *pr_timer = (result * periode) / unit;          //Calcul valeur du PeriodRegister pour avoir la periode voulue
}
