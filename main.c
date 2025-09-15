#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "gamelib.h"

struct Mago Mago1;
struct Mago Mago2;

int main(void) {
  system("clear");
  titolo();
  storia();
  double gioca=1; //variabile che verifica se sia impostato il gioco
  double rompi = 0; //variabile che verifica se si vuole re impostare il gioco
  double scelta; //variabile scelta azione utente
  int a = 0; //variabile che fa uzìscire dal do while e fa finire il gioco
  int n = 0; //numero carte mazzo
  printf( ""bianco "Salve giocatore cosa vuole fare?");
  do {
    printf("Premere: \n" blu "[1]" bianco" Impostare il gioco\n" blu "[2]"bianco" Combattere \n" blu "[3]"bianco" Terminare gioco\n");
    scanf("%lf", &scelta );
    stdin=freopen(NULL,"r",stdin);
  if (gioca == 1) { //se il gioco non è ancora stato impostato
    while((((int)scelta) < 1  ||  ((int)scelta) >3  ) || ((int)scelta == 2) ){
     if (scelta == 2) {
       printf("Devi prima impostare il gioco, premere: \a \n" blu "[1]" bianco" Impostare il gioco \n" blu "[3]" bianco" Terminare gioco\n");
       scanf("%lf", &scelta );
       stdin=freopen(NULL,"r",stdin);
     }
     else if(scelta == 1 && scelta ==3){
        break;
     }
     else if((scelta != 1) && (scelta != 2) && (scelta != 3)){
        printf("Inserisci numero valido, premere: \a \n" blu "[1]" bianco" Impostare il gioco \n" blu "[2]" bianco" Combattere \n" blu "[3]" bianco" Terminare gioco\n");
        scanf("%lf", &scelta );
        stdin=freopen(NULL,"r",stdin);
      }
    }
    gioca = 2;
  }
  else if(gioca == 2){
    if ((((int)scelta)==1)) {
        printf("Hai già impostato e confermato le impostazioni di gioco, sicuro di voler reimpostare il gioco? " blu "[1]" bianco"si" blu "[2]" bianco"no\n");
        scanf("%lf", &rompi );
        stdin=freopen(NULL,"r",stdin);
        while (((int)rompi != 1) && ((int)rompi !=2)) {
          printf("Inserisci numero valido: \a");
          scanf("%lf", &rompi );
          stdin=freopen(NULL,"r",stdin);
        }
        if ((int)rompi == 1) {
          dealloca(&Mago1,&Mago2); //dealloca le carte create precedentemente
        }
        else if ((int)rompi == 2) {
          printf("Scegliere tra " blu "[2]" bianco" Combattere e " blu "[3]" bianco" Terminare gioco \a\n");
          scanf("%lf", &scelta );
          stdin=freopen(NULL,"r",stdin);
          while ( (((int)scelta)!=2) &&(((int)scelta)!=3) ) {
            printf("Inserisci numero valido, premere: \a \n" blu "[2]" bianco" Combattere \n" blu "[3]" bianco" Terminare gioco\n");
            scanf("%lf", &scelta );
            stdin=freopen(NULL,"r",stdin);
          }
        }
     }
    else if (((int)scelta == 2)||((int)scelta == 3)){} //solo per aiuatare la visualizzazione
   }
    switch ((int)scelta) {
      case 1:
       imposta_gioco( &Mago1 , &Mago2, &n);
       system("clear");
       break;
      case 2:
       combatti(&Mago1 , &Mago2, n);
       gioca = 1;
       sleep(4);
       break;
      case 3:
       a = 0;
       termina_gioco( &a , &gioca, &Mago1 , &Mago2, n);
       break;
    }
  }while(a != 1);
  return 0;
}


