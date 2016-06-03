/* 
 * File:   uart.h
 * Author: bocal
 *
 * Created on June 3, 2016, 2:44 PM
 */

#ifndef UART_H
#define	UART_H

#include "types.h"

#define REGISTER_BAUD_RATE U1BRG;

// Focntion qui calcul le Baud Rate // check du speed mode ?????
// Pas forcement utile pck c'est pas comme un timer que l'on vas devoir odifier
// doit checker PBCLK


void    marvin_setup_baud_rate();
void    marvin_setup_uart();
void    marvin_send_message();
void    marvin_receive_message();
#endif	/* UART_H */

