/*
 * File:   Ir.h
 * Author: bocal
 *
 * Created on June 3, 2016, 2:26 PM
 */

#ifndef IR_H
#define	IR_H

#define PIN_IR 1
#define IR_CAPTURE 11       // Nbr de capture a effectue pour le tri de valeur
#define IR_SCOPE   100         // Portee du capteur, (Valeur max pour laquel le booleen vaudra 1)

void    marvin_setup_ir();
u16    capture_ir(u32 *conf_timer, u32 *pr, u32 *timer);

#endif	/* IR_H */