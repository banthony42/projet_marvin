#include "timer.h"
#include "uart.h"
#include "types.h"
#include <p32xxxx.h>

/*
 *  Fonction qui set le BAUD RATE automatiquement en fonction des reglages OSCILLATOR
 */
// U1Rx -> RF2
// U1Tx -> RF3
void    marvin_setup_baud_rate()
{
    // En Dur pour l'instant
    REGISTER_BAUD_RATE = marvin_calcul_oscillator_prescaler() / (4 * BAUD_RATE) - 1;
}

/*
 *  Fonction de config de l'UART
 *  Param1: Adresse du mode register de l'UART (UxMODE)
 *  Param2: Adresse du Status / Control register (UxSTA)
 */

void    marvin_setup_uart(u32 *uart_reg, u32 *uart_status)
{
    *uart_reg = 0 | BRGH | PDSEL_00 |  STSEL_0 ;    // config de l'UART avec define choisit
    U1STAbits.URXISEL =2;
    marvin_setup_baud_rate();                               // baud rate calculer en auto
    *uart_status = 0 | UTXEN_1 | URXEN_1;                  // Receive / Transmit enabled
    *uart_reg |= UART_ON;
}

/*
 *  Fonction qui envoi un tableau de donnees en UART
 *  Param1: Tableau a envoyer
 *  Param2: Size du Tableau
 *  Param3: Adresse du Transmit Register (UxTCXREG)
 *  Param4: Adresse du Status/Control Register (UxSTA)
 *  Param5: Adresse config Register du TIMER a utiliser (TxCON)
 *  Param6: Adresse du seuil du TIMER a utiliser (PRx)
 *  Param7: Adresse du compteur du TIMER a utiliser (TMRx)
 */

void    marvin_send_message(u8 *tab, u8 size, u32 *uart_send, u32 *uart_status, u32 *conf_timer, u32 *pr, u32 *timer)
{
    u8 i = 0;
   // marvin_set_periode(pr, 1, TYPE_A, conf_timer, TIME_MSEC);
 
    marvin_set_periode(MARVIN_PR4, 20, TYPE_B, MARVIN_CONF_TIMER4, TIME_MSEC);
    while (i < size)
    {
        if (U1STAbits.UTXBF == 0) // check si le buffer est vide pour envoyer le byte
        *uart_send = tab[i++];
      //  TMR4 = 0;
        //while (TMR4 < PR4);
    }
    //*uart_status &= OERR_0; 0b111000111 a voir
}

/*
 *  Fonction qui remplit les donnees recus dans un tableau
 *  Param1: Tableau a remplir
 *  Param2: Size du Tableau a remplir
 *  Param3: Adresse du receive register (UxRXREG)
 *  Param4: Adresse du Status/Control register (UxSTA)
 *  Param5: Adresse Receive buffer(read only) (UxSTA.bits.URXDA, 0 = buffer empty / 1 = buffer has data)
 */

void    marvin_receive_message(u8 *tab, u8 size, u32 *uart_receive, u32 *uart_status, u32 *is_receive)
{
    u8 i = 0;
    u8 clear = -1;



    while (U1STAbits.URXDA && i < 20)
    {
        *tab++ == U1RXREG;
        ++i;
        _nop();
        
    }
    if (U1STAbits.OERR == 1)
        {
            U1STAbits.OERR = 0;

        }

}
