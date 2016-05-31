/*
 * Auteur : abary, amulin, banthony, tbelmaison
 * Premiere Version du projet Marvin sur le PIC32MX340F512H
 * 
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "types.h"

/*
 * MAAAAAAAAAAAAAAIIIIIIIIIIIIIIIIIIIIIIIIIINNNNNNNNNNNN
 */

/*
 * Fonction qui attend une donne en degree (de 0 a 180) pour faire pivoter le
 * servo
 */


//OC1/ RDO -> pin 46
void    marvin_servo_write(s8 teta)
{
    teta = 0;
}

int main()
{
    while (1)
    {
        
    }
    return (0);
}