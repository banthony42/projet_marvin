
/*
 * Prototype projet marvin
 */

#define BUTTON 5
#define LED 13
#define E_S1
#define E_S2

void setup() {
  //Init du Button
   pinMode(BUTTON, INPUT);
   // Init de la Led a l'etat eteind
   pinMode(LED, OUTPUT);
   digitalWrite(LED, HIGH);
   //Init du baud rate du monitor
   Serial.begin(9600); 
}

/*
 * fonction qui tri par insertion
 * Param1: tableau qui contiendras les valeurs triees
 * Param2: taille du tableau
 * Param3 valeur a inserer
 */
void  tri_insertion(int *tab, int size, int valeur)
{
  int *pos;
  
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

/*
 * Retourne la medianne d'une serie de valeur
 * Param1: tableau de valeurs, le tableau doit etre trier par ordre croissant
 * Param2 : Taille du taleau
 * Return : La medianne 
 */
int   calcul_median(int *tab, int size)
{
  int index;

  index = (size + 1) / 2;
  if ((size + 1) % 2 == 0)
    return (*(tab + index -1 )); // -1 car on commenc a comtper a partir de zero;
   else
   return ( (*(tab + index - 1) + *(tab + index )) / 2) ;
}

/*
 * Imprime un tableau sur le monitor pour le debug
 * Param1 : tableau a afficher
 * Param2 : taille du tableau
 */
void  print_tab(int *tab, int size)
{
  while (size)
  {
    Serial.println(*tab);
    size--;
    tab++;
  }
  Serial.println("--------------------");
}

int tab[12] = {0};
int test[12] = { 3, -4, 2 , 1 ,56, 76, 87, 98, 54, 34, 5, 104};
int size = 0;

void loop() {
// test du button
  if (digitalRead(BUTTON) == HIGH)
  {
     delay(500);
  }
}
