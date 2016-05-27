#include <Servo.h>


/*
 * Prototype projet marvin
 */

#define BUTTON 5
#define LED 13
#define E_S1 8
#define E_S2 6
#define T_S1 9
#define T_S2 7
#define SERVO 11

Servo servo1; // objet servo
void setup() {
  //Init du Button
   pinMode(BUTTON, INPUT);
   // Init de la Led a l'etat eteind
   pinMode(LED, OUTPUT);
   digitalWrite(LED, HIGH);
   //Init du baud rate du monitor
   Serial.begin(9600);
   //Init des Sonars
   pinMode(T_S1, OUTPUT); 
   pinMode(T_S2, OUTPUT);
   digitalWrite(T_S1, LOW);
   digitalWrite(T_S2, LOW);
   pinMode(E_S1, INPUT);
   pinMode(E_S2, INPUT);   
   //I11nit su servo
  // pinMode(SERVO, OUTPUT);
  servo1.attach(11);
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
  int nbrzero = 0;

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

#define SIZE_SONAR 11
int   capture_sonar(int echo, int trigger)
{
  int tab[SIZE_SONAR] = {0};
  int size = 0;

  
  while (size < SIZE_SONAR)
  {
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);
    tri_insertion(tab, size, pulseIn(echo, HIGH) / 58);
    ++size;
  }
  print_tab(tab, SIZE_SONAR); // pour les tests
  return (calcul_median(tab, SIZE_SONAR));
  
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
    int s1, s2 = 0;
    s1 = capture_sonar(E_S1, T_S1);
    s2 = capture_sonar(E_S2, T_S2);
    if (s1 > s2)
    {
       Serial.println("a gauche");
      servo1.write(0);
      // tourner le servo a gauche
    }else
    {
      Serial.println("a droite");
      servo1.write(180);
      //tourner le servo a droite
    }
    //test du sonar2
     delay(500);
  }
}
