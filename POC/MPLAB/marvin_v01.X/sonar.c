
#include <p32xxxx.h>
#include <sys/attribs.h>
#include "sonar.h"
#include "types.h"
#include "tools.h"


// va falloir envoyer les PINS a definir en entree et en sortie, le trigger LATF pour modifier letat de la sortie
// En faites on sen fous des interrupt..

/*
void    marvin_setup_interrupt_sonar1()
{
}

void    marvin_setup_interrupt_sonar2()
{
}
/*
 * Fonction qui init les pins pour utiliser le Sonar
 * Param 1: L'objet Sonar
 * Param 2: La pin trig a definir a l'etat Sortie
 * Param 3: L'etat de la pin trig a definir a 0;
 * Param 4: La pin echo a definir comme input
 * Param 5: Le Registre de lecture la pin echo
 */

void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read)
{
    *trig_etat |= 0b0;
    *trig_pin &= 0b11111110;     // (de base tout les bits du registre TRISE sont a 1 donc mask pour mettre a 0 le bit 0)
    *echo_pin |= 0b1 << 9;      // mask pour mettre pin de echo en input
    sonar->state_trig_pin = trig_etat;
    sonar->read_echo_pin = echo_read;
}

/*
 * Fonction qui envoi un signal sur le Trigger pour demander la mesure
 * Param 1: L'objet Sonar
 */

void    marvin_trigger(m_sonar *sonar)
{
    *(sonar->state_trig_pin) |= 0b1;
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    *(sonar->state_trig_pin) &= 0b0;
}

/*
 * Fonction qui lit le retour sur echo, et return la mesure en cm
 * Param 1: L'objet Sonar
 */

u16      marvin_pulseIn(m_sonar *sonar)
{
    u16 ret;
    TMR1 = 0;
    while (PORTDbits.RD9 == 0)//(*(sonar->read_echo_pin) & (0b1 << 9))== 0) //On attend un front montant
        if (TMR1 == PR1)            // Si la tempo est ecoule on return erreur (-1)
            return (6066);          // Code erreur
    TMR1 = 0;
    while (PORTDbits.RD9 == 1)//(*(sonar->read_echo_pin) & (0b1 << 9)) == 1)
        ret = TMR1;
    return (ret / 58); // Voir pour faire un calcul precis surtout si on utilise un TIMER aleatoire
}

/*
 * Fonction Maitre qui effectue une serie de x mesures (NBR_CAPTURE) et return la mediane
 * Param 1: L'objet Sonar
 */
/*
u16      marvin_capture(m_sonar *sonar)
{
    u8 i = 0;
    u16 tab[NBR_CAPTURE] ={0};

    while (i < NBR_CAPTURE)
    {
        marvin_trigger(sonar); //on envoie le trig
    // tab[i] = marvin_pulseIn(sonar); // On lit le retour
    // Fonction de tri (c.f arduino)
        if (marvin_tri_insertion(tab, i, marvin_pulseIn(sonar)) == 6066)    // Si erreur
            return (6066);                                                  // Return erreur
        ++i;
    }
    return (marvin_calcul_median(tab, NBR_CAPTURE));
    // fonction de medianne (c.f arduino)
}
*/