#include "types.h"
#include "tools.h"
#include "timer.h"
#include "Ir.h"
#include <p32xxxx.h>
#include <sys/attribs.h>

u16   ir_convert_tension_cm(u16 tension)
{
    u16 test;
    if (tension > 2990)
    {
        test =  (tension * -63 + 256880) / 10000;
        return (tension * -63 + 256880) / 10000;
    }
        
    if (tension > 2300)
    {
        test =  (tension * -44 + 202220) / 10000;
        return (tension * -44 + 202220) / 10000;
    }
    if (tension > 1300)
    {
        test =  (tension * -143 + 385710) / 10000;
        return (tension * -143 + 385710) / 10000;
    }
    if (tension > 750)
    {
        test =  (tension * -441 + 730880) / 10000;
        return (tension * -441 + 730880) / 10000;
     }
     
     if (tension > 510)
     {
         test = (tension * -1111 + 1166700) / 10000 ;
        return (tension * -1111 + 1166700) / 10000;
     }
     return (tension * -2000 + 1600000) / 10000;


}
/*
 * Param1 : Registre de configuration TIMER a utiliser pour la capture (En principe le TMR4)
 * Param2 : Registre pour la Periode du TIMER
 * Param3 : Registre du TIMER
 */
u16    capture_ir(u32 *conf_timer, u32 *pr, u32 *timer)
{
    u8 i = 0;
    u16 tab[IR_CAPTURE];

    marvin_set_periode(pr ,100, TYPE_B, conf_timer, TIME_MSEC); // Definition d'une periode sur le TIMER pour le sampling
    while (i < IR_CAPTURE)
    {
        AD1CON1bits.SAMP = 1;                                   // On lance le sampling
        *timer = 0;
        while (*timer != *pr);
        AD1CON1bits.SAMP = 0;                                   // On lance la conversion
        while (!(AD1CON1 && 0x0001));                           // On attend la fin de la conversion
        marvin_tri_insertion(tab, i, ADC1BUF0);                 // Lecture du signal recu encoye dans la Fonction de tri (c.f arduino)
        ++i;
    }
    return (ir_convert_tension_cm(marvin_calcul_median(tab , IR_CAPTURE) * 3300 / 1024));            // Fonction de mediane (c.f arduino)
}

/*
 * Fonction de configuration d'une Input Analogique pour le capteur IR
 */
void    marvin_setup_ir()
{
    LATAbits.LATA1 = 0;
    TRISAbits.TRISA1 = 1;   // RA1 en input
    /*
     * Configuration de l'ADC
     */
    AD1CHSbits.CH0SA = PIN_IR;  // On selectionne le pin AN1 comme input positif du multiplexer A.
    //------------------------------------------------------------------------//
    AD1CHSbits.CH0NA = 0;       // On selectionne Vr- comme tension de ref negative du multiplexer A
    AD1CON1bits.FORM = 0;       // Formatage du resultat de la conversion en entier non-signe sur 16 bits (10 bits actifs)
    AD1CON1bits.SSRC = 0;       // Sample clock source en mode manuel : il faudra clear le bit SAMP pour arreter le sample et initier la conversion
    AD1CON2bits.VCFG = 0;       // On selectionne AVDD et AVSS comme reference de tension pour Vr+ et Vr-
    AD1CON2bits.CSCNA = 0;      // Ne pas scanner les inputs (car on ne lit qu'un seul pin, AN5)
    AD1CON2bits.SMPI = 0;       // 1 conversion par interrupt
    AD1CON2bits.BUFM = 0;       // On remplit le buffer avec les 16 bits d'un seul coup
    AD1CON2bits.ALTS = 0;       // On utilise uniquement le multiplexer A
    AD1CON3bits.ADRC = 0;       // Selection de PBCLK comme clock de conversion
    AD1CON3bits.ADCS = 0;       // Prescaler de 2 pour cette clock. TAD = TPB / 2 ; Donc TAD = 0.5MHz
    AD1CON3bits.SAMC = 1;       // Sample time de 1 TAD. Ce n'est peut-etre pas utile, car en principe nous sommes en sampling manuel
    AD1CON1bits.ON = 1;         // On active le module ADC
}

