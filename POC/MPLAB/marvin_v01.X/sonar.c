
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
*/
/*
 * Fonction qui init les pins pour utiliser le Sonar
 * Param 1: L'objet Servo
 * Param 2: La pin trig a definir a l'etat Sortie
 * Param 3: L'etat de la pin trig a definir a 0;
 * Param 4: La pin echo a definir comme input
 * Param 5: Le Registre de lecture la pin echo
 */
void    marvin_set_sonar(m_sonar *sonar, u32 *trig_pin, u32 *trig_etat, u32 *echo_pin, u32 *echo_read)
{
    *trig_etat = 0;
    *trig_pin = 1;
    *echo_pin = 0;
    sonar->trig_pin = trig_etat;
    sonar->echo_pin = echo_read;
   // sonar->i = 0;
    // init du tableau ?????????
}


// Ici on lui envoi LATxbits
void    marvin_trigger(m_sonar *sonar)
{
    *(sonar->trig_pin) = 1;
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    asm volatile("nop");
    *(sonar->trig_pin) = 0;
}

// pas d'interrupt
// on vas utiliser TMR1 pour les tests  apres voir si on le definie dans le setup ou on utilise
// un timer au PIF car de toute facon on seras bloquant
u16      marvin_pulseIn(m_sonar *sonar)
{
    u16 ret;
    while (*(sonar->echo_pin) == 0); //On attend un front montant; Rajouter une protection si on capte pas l'etat haut

    TMR1 = 0;
    // Rajouter une protection si l'etat de la pin reste tout le temps a letat haut
    while (*(sonar->echo_pin) == 1)
        ret = TMR1;
    return (ret / 58); // Voir pour faire un calcul precis surtout si on utilise un TIMER aleatoire
}


// retourne la medianne
// voir pour envoyer le timer...
u16      marvin_capture(m_sonar *sonar)
{
    u8 i = 0;
    u16 tab[NBR_CAPTURE] ={0};

    while (i < NBR_CAPTURE)
    {
    marvin_trigger(sonar); // on envoie le trig
  //  tab[i] = marvin_pulseIn(sonar); // On lit le retour
    // Fonctionde tri (c.f arduino)
    
    marvin_tri_insertion(tab, i, marvin_pulseIn(sonar));
     ++i;
    }
    return (marvin_calcul_median(tab, NBR_CAPTURE));
    // fonction de medianne (c.f arduino)
}
