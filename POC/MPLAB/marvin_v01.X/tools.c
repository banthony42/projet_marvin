#include "types.h"
#include "tools.h"


/*
 * Retourne la medianne d'une serie de valeur
 * Param1: tableau de valeurs, le tableau doit etre trier par ordre croissant
 * Param2 : Taille du taleau
 * Return : La medianne
 */
u16   marvin_calcul_median(u16 *tab, u8 size)
{
  u8 index;
  u8 nbrzero = 0;

  // Pour pallier au bug du Sonar on va ignorer les zeros;

  while (*(tab + nbrzero) == 0 && nbrzero < size)
      ++nbrzero;
  index = (size - nbrzero +  1) / 2 ;
  if (index  > size)
      return (0);
  if ((size + 1 ) % 2 == 0)
  {
    return (*(tab + index -1 + nbrzero)); // -1 car on commenc a comtper a partir de zero;
  }
   else
   return ( (*(tab + index - 1 +nbrzero) + *(tab + index +nbrzero)) / 2) ;
}


/*
 * fonction qui tri par insertion
 * Param1: tableau qui contiendras les valeurs triees
 * Param2: taille du tableau
 * Param3 valeur a inserer
 */
 
void  marvin_tri_insertion(u16 *tab, u8 size, u16 valeur)
{
  u16 *pos;
  
  while (size && *tab < valeur)
  {
    ++tab;
    --size;
  }
  pos = tab;
  if (size)
  {
    while (size)
    {
      ++tab;
      --size;
    }
    while (tab > pos)
    {
      *tab = *(tab - 1);
      tab--;
    }
  }
  *pos = valeur;
}

