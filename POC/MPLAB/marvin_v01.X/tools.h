/* 
 * File:   tools.h
 * Author: Amulin, Aodren, Banthony, Tbeauman.
 *
 * Created on June 2, 2016, 7:02 PM
 */

#ifndef TOOLS_H
#define	TOOLS_H
#include "types.h"

u16 map(u16 x, u16 in_min, u16 in_max, u16 out_min, u16 out_max);
u16 marvin_tri_insertion(u16 *tab, u8 size, u16 valeur);
u16 marvin_calcul_median(u16 *tab, u8 size);

#endif	/* TOOLS_H */

