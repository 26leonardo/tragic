#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include "gamelib.h"

//DICHIARAZIONI FUNZIONI GAMELIB.C
static void mazzo(struct Mago *Mago, int num_carte, unsigned int classe); //crea mazzo
static void stampa_mazzo(struct Mago* p_mago);
static void elimina_mazzo(struct Mago* p_mago);

static void pesca(struct Mago *p_mago);
static void gioca_posiziona(struct Mago *p_mago_attacco, struct Mago *p_mago_difesa, int*posiziona);
static void attacca(struct Mago *p_mago_attacco, struct Mago *p_mago_difesa, int* attacca);
static void passa(int*giocatore, int*pescata, int*posiziona, int*attacca, int*pv);
static void stampa_campo(struct Mago *p_mago);
static void stampa_mano(struct Mago *p_mago);

//DEFINIZIONI FUNZIONI
void titolo(void){
  printf(""magenta"                              ,,,,                                                                               ,,,,,         \n");
  printf(" ████████████████████▄═ ,▄▄██▀▀▀▀▀███▄╖              '██████▄▀              ▄▄████████▄▄▄▄P,    ▀█████▀▄═     ▄▓██▀▀▀████▄▄▓ ▄\n");
  sleep(1);
  printf("  ██,▌▀▀▀█████▀▀▀▀██▄▀   ████▐▀  `▀▀████▌╕            █████▌█            ,▄███▀▄▀  `▀▀███▀▄▀      ███▌█     ▄███,▓▀   '▀███╓▀ \n");
  printf("   ▀█    █████     ▐▀    ████▐      ▐███▌█           ▄█,████▄▌          ▄████▄▀        ▀▀▄`       ███▌█    ▄███ █       ▐█▄▀  \n");
  sleep(1);
  printf("         █████           ████▐     ,████,█       ,▓▄▄█▀▌ ▀███▄▌,▄,      ████ █▄██       '         ███▌█   ▐████▐▌         ▀   \n");
  printf("         █████           █████▄,▄▄███▀▄▄▀       ,████▌▓   ███████▄▌    ▐████▐▌▀██▓▓▓▓▓▓▓███▀▄     ███▌█   ▐███▌▐              \n");
  sleep(1);
  printf("         █████        ▐██████▀▀▀▀██▄▀▀            ▐███▄▀▄ ▄████▐▄æ▀▄   ▐████▐▌  ▀▀▀▀▀▀████▐▌      ███▌█   ▐███▌▐                \n");
  printf("         █████         Æ▀████▐▀  ▐██▄▀            ██▐▀██▓██▀████▀       ████ █        ▐███▐▌      ███▌█   ▐████▐▌         ▄▄, \n");
  sleep(1);
  printf("         █████           ████▐    ▀██▄▀,         ██▌█  ▀█▀Æ ▐███▌█      ╙███▌▀,       ▐███▐▌      ███▌█    ████▄█        ,█▌█  \n");
  printf("         █████           ████▐     ████▄▌      ╓███▐▌    ▀   ▀███▌▌       ▀████▄      ▐███▐▌      ███▌█     ▀███▄▀,     ,██▐▌ \n");
  sleep(1);
  printf("       ,▄█████▌        ,▄█████▌    ▐████▄▀▓, ╓▓██████,      ,▄█████▌╖       ▀▀███▄▄▄▄▄██████,   ╓▓█████▄      ▀█████▄▄▄▓█▀▄▀ \n");
  printf("       ████████▓      ▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀       ▀▀▀▀▀▀▀▀▀          ▀▀▀▀▀▀▀▀▀▀▀     ▀▀▀▀▀▀▀▀▀        ▀▀▄▄▄▄▄▄▀▀     \n" bianco"");
  sleep(1);
}

void storia(void){
  printf(""blu"STORIA:\n");
  sleep(0.80);
  printf(""blu_chiaro "Due Maghi si affrontano in un duello uno-contro-uno su una piana ventosa vicina ad Ravnika, \n");
  sleep(0.80);
  printf("la Città delle Gilde. Gli incantesimi che possono lanciare sono rappresentati da un mazzo di \n");
  sleep(0.80);
  printf("carte ciascuno. Crea il tuo personaggio e in base alla classe scelta avrai creature personalizzate\n");
  sleep(0.80);
  printf("e anche le caratteristiche delle carte cambieranno.\n");
  sleep(1.50);
  printf(""blu"REGOLE:\n");
  sleep(0.80);
  printf(""blu_chiaro "Ogni giocatore inizia con 5 carte in mano, al max se ne possono avere 6. Si può pescare solo \n");
  sleep(0.80);
  printf("una volta a turno, lo stesso vale per l'attacco e per il posizionamento di una carta Creatura \n");
  sleep(0.80);
  printf("nel campo o del gioco instaneo delle carte Cura/ Attacco generale/ Elimina creatura. I PV dei \n");
  sleep(0.80);
  printf("Maghi sono 20 e al primo turno, chi inizia, non può attaccare con una creatura. Una creatura  \n");
  sleep(0.80);
  printf("può attaccare direttamente il Mago avversario se il numero di creature presenti sul campo di \n");
  sleep(0.80);
  printf("chi attacca sono maggiori del numero di creature presenti nel campo avversario\n");
  sleep(1.50);
  printf("In base alla classe scelta si hanno dei booster:\n");
  sleep(0.80);
  printf(""rosso"Tenebra:"blu_chiaro " Le carte di Attacco generale hanno il doppio dei punti \n");
  sleep(0.80);
  printf(""verde"Vita:"blu_chiaro " Le sue creature hanno metà vita in più e quindi anche attacco\n");
  sleep(0.80);
  printf(""giallo"Luce:"blu_chiaro " Le carte cura hanno tre volte e mezzo il loro valore\n" bianco"");
  sleep(1.50);
  printf("Scrivere "magenta"\"Tragic\" "bianco" per andare al menù : ");
  char tragic1[7]={"Tragic"};
  char tragic2[7]={"tragic"};
  char tragic_imp[7];
  stdin=freopen(NULL,"r",stdin);
  fgets(tragic_imp,7,stdin);
  stdin=freopen(NULL,"r",stdin);

  while (( strcmp(tragic_imp, tragic1) != 0) && ( strcmp(tragic_imp, tragic2) != 0)) {
    printf("\nDevi scrivere \"Tragic\" \a \n" );
    fgets(tragic_imp,7,stdin);
    stdin=freopen(NULL,"r",stdin);
  }
  system("clear");
}

void crediti(void){
  printf("\n\n\n\n\t" blu " TRAGIC! - Crediti di gioco\n");
  printf("\n\t GAME DIRECTOR: Leonardo Billi");
  printf("\n\t GAME DESIGNER: Leonardo Billi");
  printf("\n\t PROGRAMMER: Leonardo Billi");
  printf("\n\t GAME TESTER: Leonardo Billi");
  printf("\n\t @copyright 2022 - GIOCO CHE NON RIPRENDE DA MAGIC" bianco"\n\n\n");
}

void imposta_gioco(struct Mago *p_mago_1, struct Mago *p_mago_2, int* n){
  double conferma_tot = 1; //variabile che verifica che si siano accettate tutte le condizioni impostate, in quel caso fa uscire dal do while
  do {
      double conferma1 = 1; //variabile che verifica che si siano accettate tutte le condizioni impostate per il primo mago
      double conferma2 = 1; //variabile che verifica che si siano accettate tutte le condizioni impostate per il secondo mago
      double m = 0; //variabile temporanea per la memorizzaione del numero delle carte
      p_mago_1->PV = 20;
      p_mago_2->PV = 20;

      do {
        stdin=freopen(NULL,"r",stdin);
        printf("Inserire nome primo mago: ");
        fgets(p_mago_1->nome,24,stdin);
        stdin=freopen(NULL,"r",stdin);
        int g = strlen(p_mago_1->nome);
        for (int i = 1; i <= g; i++) {
          if (i == g) {
            p_mago_1->nome[i-1]= '\0';
          }
        }
        printf("\nScegliere la classe di "ciano"%s"bianco" tra: \ntenebre " blu "[1]" bianco", vita " blu "[2]" bianco" o luce " blu "[3]" bianco"\n", p_mago_1->nome);
        double c = 0;
        scanf("%lf", &c);
        stdin=freopen(NULL,"r",stdin);
        while ((c!=1) && (c!=2) && (c!=3) ){
          printf("inserire un numero valido = \a");
          scanf("%lf", &c);
          stdin=freopen(NULL,"r",stdin);
        }
        int s =(int)c;
        switch (s) {
            case 1:
                p_mago_1->Classe = Tenebre;
                break;
            case 2:
                p_mago_1->Classe = Vita;
                break;
            case 3:
                p_mago_1->Classe = Luce;
                break;
        }
        printf("Confermi tutte le scelte fatte fino ad ora? Premere " blu "[1]" bianco" per si e " blu "[2]" bianco" per no: ");
        scanf("%lf", &conferma1 );
        stdin=freopen(NULL,"r",stdin);
        while (conferma1 != 1 && conferma1 != 2) {
          printf("inserire un numero valido: \a");
          scanf("%lf", &conferma1);
          stdin=freopen(NULL,"r",stdin);
        }
      } while(conferma1  == 2);

      do {
        stdin=freopen(NULL,"r",stdin);
        printf("Inserire nome secondo mago: ");
        fgets(p_mago_2->nome,24,stdin);
        stdin=freopen(NULL,"r",stdin);
        int g = strlen(p_mago_2->nome);
        for (int i = 1; i <= g; i++) {
          if (i == g) {
            p_mago_2->nome[i-1]= '\0';
          }
        }
        printf("\nScegliere la classe di "ciano"%s"bianco" tra: \ntenebre " blu "[1]" bianco", vita " blu "[2]" bianco" o luce " blu "[3]" bianco"\n", p_mago_2->nome);
        double c = 0;
        scanf("%lf", &c);
        stdin=freopen(NULL,"r",stdin);
        while ((c!=1) && (c!=2) && (c!=3) ){
          printf("inserire un numero valido = \a");
          scanf("%lf", &c);
          stdin=freopen(NULL,"r",stdin);
        }
        int s =(int)c;
        switch (s) {
            case 1:
                p_mago_2->Classe = Tenebre;
                break;
            case 2:
                p_mago_2->Classe = Vita;
                break;
            case 3:
                p_mago_2->Classe = Luce;
                break;
        }
        printf("Confermi tutte le scelte fatte fino ad ora? Premere " blu "[1]" bianco" per si e " blu "[2]" bianco" per no: ");
        scanf("%lf", &conferma2 );
        stdin=freopen(NULL,"r",stdin);
        while (conferma2 != 1 && conferma2 != 2) {
          printf("inserire un numero valido: \a");
          scanf("%lf", &conferma2);
          stdin=freopen(NULL,"r",stdin);
        }
      } while(conferma2 == 2);

      stdin=freopen(NULL,"r",stdin);

      printf("Scegli il numero di carte dei mazzi (tra 20-60): ");
      scanf("%lf", &m);
      stdin=freopen(NULL,"r",stdin);
      while (m<20 || m>60) {
        printf("inserire un numero valido: \a");
        scanf("%lf", &m);
        stdin=freopen(NULL,"r",stdin);
      }
      *n = (int)m;

      mazzo(p_mago_1, *n, p_mago_1->Classe);
      mazzo(p_mago_2, *n, p_mago_2->Classe);
      stampa_mazzo(p_mago_1);
      puts("");
      stampa_mazzo(p_mago_2);
      puts("");
      printf("Accetti tutto quello impostato fino ad ora? Premere " blu ""blu"[1]"bianco"" bianco" per si e " blu "[2]" bianco" per no: " );
      scanf("%lf", &conferma_tot );
      stdin=freopen(NULL,"r",stdin);
      while (conferma_tot != 1 && conferma_tot != 2) {
        printf("inserire un numero valido: \a");
        scanf("%lf", &conferma_tot);
        stdin=freopen(NULL,"r",stdin);
      }
      if (conferma_tot == 2) { //dealloca le carte create
        elimina_mazzo(p_mago_1);
        elimina_mazzo(p_mago_2);
      }
  } while(conferma_tot == 2);
}

static void mazzo(struct Mago *Mago, int num_carte, unsigned int classe){
  srand((unsigned)time(0));

  Mago->p_prima_carta = (struct Carta*) calloc(1,sizeof(struct Carta)); //assegno a mago il puntatore alla prima carta
  struct Carta *p_carta_precedente = Mago->p_prima_carta;               //assegno ad un puntatore il puntatore trovato così da non riscrivere sempre Mago-> ecc
  p_carta_precedente->p_carta_succ = NULL;                              //inizializzo all'interno dello struct, il punt a carta successivo a NULL (evitare errori)
  struct Carta *p_nuova_carta = NULL;                                   //definisco il puntatore della Carta che collegherò in coda
  for (int i = 1; i <= num_carte; i++) {
    if (i != num_carte) {                                               //tutte le carte meno l'ultima
      p_nuova_carta = (struct Carta*) calloc(1,sizeof(struct Carta));   //dico al puntatore dove preservare memoria
      p_nuova_carta->p_carta_succ = NULL;                               //inizializzo all'interno dello struct, il punt a carta successivo a NULL
      p_carta_precedente->p_carta_succ = p_nuova_carta;                 //collego i due struct assegnando all'interno dello struct precedente il puntatore alla carta succ

      if(i<((int)(num_carte/4))){                                       //inserisco i punti vita
        p_carta_precedente->punti_vita_danno_cura = (rand() % 2) + 7;
      } else if ((i>=((int)(num_carte/4))) && (i<((int)(num_carte/2)))){
        p_carta_precedente->punti_vita_danno_cura = (rand() % 2) + 5;
      } else if ((i>=((int)(num_carte/2))) && (i<((int)(3*(num_carte/4))))) {
        p_carta_precedente->punti_vita_danno_cura = (rand() % 2) + 3;
      } else if ((i>=((int)(3*(num_carte/4)))) && (i<((int)num_carte))) {
        p_carta_precedente->punti_vita_danno_cura = (rand() % 2) + 1;
      }

      int r =  rand()%100;
      if(r >= 0 && r < 40){
        p_carta_precedente->Tipo = Creatura;
        if(classe == 2){ //vita
          p_carta_precedente->punti_vita_danno_cura += ((p_carta_precedente->punti_vita_danno_cura)/2);
        }
      }else if(r >= 40 && r < 65){
        p_carta_precedente->Tipo = Rimuovi_creatura;
      }else if(r >= 65 && r < 85){
        p_carta_precedente->Tipo = Infliggi_danno;
        if(classe == 1){ //tenebra
          p_carta_precedente->punti_vita_danno_cura *= 2;
        }
      }else if(r >= 85 && r < 100){
        p_carta_precedente->Tipo = Guarisci_danno;
        if(classe == 3){ //Luce
          p_carta_precedente->punti_vita_danno_cura *= 3.5;
        }
      //inserire quello che va all'interno di p_carta_precedente
     }
     p_carta_precedente = p_nuova_carta;


    }else{
      struct Carta *p_coda = p_nuova_carta;
      Mago->p_ultima_carta = p_coda;
      p_coda->p_carta_succ = NULL;
      p_coda->punti_vita_danno_cura = (rand() % 2) + 1;

      int r =  rand()%100;
      if(r >= 0 && r < 40){
        p_coda->Tipo = Creatura;
        if(classe == 2){ //vita
          p_coda->punti_vita_danno_cura += ((p_coda->punti_vita_danno_cura)/2);
        }
      }else if(r >= 40 && r < 65){
        p_coda->Tipo = Rimuovi_creatura;
      }else if(r >= 65 && r < 85){
        p_coda->Tipo = Infliggi_danno;
        if(classe == 1){ //tenebra
          p_coda->punti_vita_danno_cura *= 2;
        }
      }else if(r >= 85 && r < 100){
        p_coda->Tipo = Guarisci_danno;
        if(classe == 3){ //Luce
          p_coda->punti_vita_danno_cura *= 3.5;
        }
      //inserire quello che va all'interno di p_coda PRIMA CARTA CHE VA PESCATA

    }
  }
 }
}
static void stampa_mazzo(struct Mago* p_mago) {
  if (p_mago->p_prima_carta == NULL){
    printf("Non ci sono carte nel mazzo!\n");
  }
  else {
    struct Carta* p_temp = p_mago->p_prima_carta;
    int i = 0;
    while (p_temp != NULL) {
      printf("--------------------------------------------------------------------\n");
      printf("%5s %d  ","Carta:", ++i);
      printf(" || ");

      if((p_temp->Tipo) == 1){
        printf(" Genere: Creatura ");
        printf(" || ");
        printf(" %5s %.2lf  ", "PV: ",p_temp->punti_vita_danno_cura);
      }
      else if ((p_temp->Tipo) == 2){
        printf(" %5s ","Genere: Elimina creatura");
        printf(" || ");
        printf(" %5s  ","Scegli bersaglio");
      }
      else if ((p_temp->Tipo) == 3){
        printf(" %5s ","Genere: Attacco generale");
        printf(" || ");
        printf(" %5s %.2lf  ", "Infliggi danno: ",p_temp->punti_vita_danno_cura);
      }
      else if ((p_temp->Tipo) == 4){
        printf(" %5s ","Genere: Cura");
        printf(" || ");
        printf(" %5s %.2lf  ", "Bonus: ", p_temp->punti_vita_danno_cura);
      }

      p_temp = p_temp-> p_carta_succ;
      puts("");
    }
    printf("--------------------------------------------------------------------\n");
  }
}
static void elimina_mazzo(struct Mago* p_mago){

  // per ogni i del ciclo, la funzione prende la prima carta e verifica se il puntatore alla prossima
  // sia nullo; in quel caso si modfica la struttura mago e si pone a NULL la prima e ulrima carta,
  //nell'altro caso si avvia uno while che si ferma alla carte prima dell'ultima, memorizzandola come
  //ultima nella struct mago e eliminando con free l'ultima carta e ponendo a NULL il puntatore alla
  // cartra successiva della carta precdente all'ultima
  while((p_mago->p_prima_carta)!= NULL) {
    struct Carta *p_prec = p_mago->p_prima_carta;

    if (p_prec-> p_carta_succ == NULL) {
      free(p_prec);
      p_mago->p_prima_carta = NULL;
      p_mago->p_ultima_carta = NULL;
    }else{
      do {
        if ((p_prec->p_carta_succ) == (p_mago->p_ultima_carta)) {
          p_prec = p_prec;
          free(p_prec->p_carta_succ);
          p_prec->p_carta_succ = NULL;
          p_mago->p_ultima_carta =  p_prec;
        }else{
          p_prec = p_prec->p_carta_succ;
        }
      } while((p_prec -> p_carta_succ) != NULL);
    }
  }
}

void dealloca(struct Mago *p_mago_1, struct Mago *p_mago_2) {
  elimina_mazzo(p_mago_1);  //funziona creata per far si che elimina mazzo rimanga una funzione static
  elimina_mazzo(p_mago_2);  //quindi non modificabile, ne chiamabile nel main.c
}

void combatti(struct Mago *p_mago_1, struct Mago *p_mago_2,  int numero_carte){
  for (int i = 0; i < 6; i++) {
    p_mago_1->mano[i] = NULL;
    p_mago_2->mano[i] = NULL;
  }
  for (int i = 0; i < 5; i++) {
    pesca(p_mago_1);
    pesca(p_mago_2);
  }
  for (int i = 0; i < 4; i++) {
    p_mago_1->campo[i] = NULL;
    p_mago_2->campo[i] = NULL;
  }

  int k = rand() % 2; //varibabile che sceglie il giocatore

  int a = 0; //variabile che impedisce di pescare più di una volta a turno
  int b = 0; //variabile che impedisce di posizionare/giocare più di una volta a turno
  int d = 3; //variabile che impedisce di attaccare più di una volta a turno e di attaccare al primo turno
  int f = 0; //variabile che fa stampare una volta a turno il nome e i PV di chi inizia
  int fine = 0; //varibile che fa terminare il while, quindi il gioco, nel turno dell'avversario se si sono finite le carte da giocare
  double c = 0; //variabile dove viene aggiornato il valore inserito da tastiera per la scelta

  if (k == 0) {
    printf("Inizia "ciano"%s"bianco"\n", p_mago_1->nome );
  } else if (k == 1) {
    printf("Inizia "ciano"%s"bianco"\n", p_mago_2->nome );
  }

  while (((p_mago_1->PV) > 0)&&((p_mago_2->PV) > 0)) {
    stdin=freopen(NULL,"r",stdin);
    if (k == 0) {
      if (f == 0) {
        printf("Menu mago "ciano"%s"bianco","ciano" PV = "magenta"%.2lf"bianco"\n", p_mago_1->nome , p_mago_1->PV);
        printf("PV mago avversario = "magenta"%.2lf"bianco"\n", p_mago_2->PV);
        f = 1;
      }
      printf("" blu "[1]" bianco" = Pesca || " blu "[2]" bianco" = Gioca/Posiziona || " blu "[3]" bianco" = Attacca || " blu "" blu "[4]" bianco"" bianco" = Passa || " blu "[5]" bianco" = Stampa campo || " blu "[6]" bianco" = Stampa mano\n");
      scanf("%lf", &c);
      stdin=freopen(NULL,"r",stdin);
      while ((c!=1) && (c!=2) && (c!=3) && (c!=4) && (c!=5) && (c!=6)){
        printf("inserire un numero valido = \a");
        scanf("%lf", &c);
        stdin=freopen(NULL,"r",stdin);
      }
      switch ((int)c) {
        case 1:
         if (a == 0) {
           pesca(p_mago_1);
           a = 1;
         }else{
           printf("Non puoi pescare due volte in un turno! Inserire un numero valido  \a \n");
         }
         break;
        case 2:
         if (b == 0) {
           b = 1;
           gioca_posiziona(p_mago_1, p_mago_2, &b);
         }else{
           printf("Non puoi giocare/posizionare due volte in un turno! Inserire un numero valido  \a \n");
         }
         break;
        case 3:
         if (d == 0) {
           attacca(p_mago_1, p_mago_2, &d);
         }
         else if (d == 3){
           printf("Non puoi attaccare al primo turno! Inserire un numero valido  \a \n");
         }
         else{
           printf("Non puoi attaccare due volte in un turno! Inserire un numero valido  \a \n");
         }
         break;
        case 4:
        if (p_mago_2 -> p_prima_carta == NULL) {
          fine = 1;
        }
        else{
          passa(&k, &a, &b, &d, &f);
        }
        system("clear");
         break;
        case 5:
         printf("Proprio campo:\n");
         stampa_campo(p_mago_1);
         printf("Campo avversario:\n");
         stampa_campo(p_mago_2);
         break;
        case 6:
         stampa_mano(p_mago_1);
         break;
      }
    }
    else if (k == 1) {
      if (f == 0) {
        printf("Menu mago "ciano"%s"bianco","ciano" PV = "magenta"%.2lf"bianco"\n", p_mago_2->nome , p_mago_2->PV);
        printf("PV mago avversario = "magenta"%.2lf"bianco"\n", p_mago_1->PV);
        f = 1;
      }
      printf("" blu "[1]" bianco" = Pesca || " blu "[2]" bianco" = Gioca/Posiziona || " blu "[3]" bianco" = Attacca || " blu "" blu "[4]" bianco"" bianco" = Passa || " blu "[5]" bianco" = Stampa campo || " blu "[6]" bianco" = Stampa mano\n");
      scanf("%lf", &c);
      stdin=freopen(NULL,"r",stdin);
      while ((c!=1) && (c!=2) && (c!=3) && (c!=4) && (c!=5) && (c!=6)){
        printf("inserire un numero valido = \a");
        scanf("%lf", &c);
        stdin=freopen(NULL,"r",stdin);
      }
      switch ((int)c) {
        case 1:
         if (a == 0) {
           pesca(p_mago_2);
           a = 1;
         }else{
           printf("Non puoi pescare due volte in un turno! Inserire un numero valido  \a \n");
         }
         break;
        case 2:
         if (b == 0) {
           b = 1;
           gioca_posiziona(p_mago_2, p_mago_1, &b);
         }else{
           printf("Non puoi giocare/posizionare due volte in un turno! Inserire un numero valido \a \n");
         }
         break;
        case 3:
         if (d == 0) {
           attacca(p_mago_2, p_mago_1, &d);
         }
         else if (d == 3){
           printf("Non puoi attaccare al primo turno! Inserire un numero valido  \a \n");
         }
         else{
           printf("Non puoi attaccare due volte in un turno! Inserire un numero valido  \a \n");
         }
         break;
        case 4:
        if (p_mago_1 -> p_prima_carta == NULL) {
          fine = 1;
        }
        else{
          passa(&k, &a, &b, &d, &f);
        }
         system("clear");
         break;
        case 5:
         printf("Proprio campo:\n");
         stampa_campo(p_mago_2);
         printf("Campo avversario:\n");
         stampa_campo(p_mago_1);
         break;
        case 6:
         stampa_mano(p_mago_2);
         break;
       }
    }
    if (fine == 1) {
      break;
    }
  }

  if (((p_mago_1->p_prima_carta) == NULL) || ((p_mago_2->p_prima_carta) == NULL)){
    if((p_mago_1->PV)<(p_mago_2->PV)){
      printf("Partita finita, vince "ciano"%s"bianco" che ha maggiori PV di "ciano"%s"bianco".\n"magenta"%5.2lf > %5.2lf"bianco"\n", p_mago_2->nome ,p_mago_1->nome , p_mago_2->PV ,p_mago_1->PV );
    }else if ((p_mago_2->PV)<(p_mago_1->PV)) {
      printf("Partita finita, vince "ciano"%s"bianco" che ha maggiori PV di "ciano"%s"bianco".\n"magenta"%5.2lf > %5.2lf"bianco"\n", p_mago_1->nome ,p_mago_2->nome , p_mago_1->PV ,p_mago_2->PV );
    }else if ((p_mago_2->PV)==(p_mago_1->PV)) {
      printf("Partita finita, PAREGGIO.\n%5.2lf = "magenta"%5.2lf"bianco"\n", p_mago_1->PV ,p_mago_2->PV );
    }
  }
  else if((p_mago_1->PV) <= 0){
    printf("Partita finita, vince indiscusso "ciano"%s"bianco"\n", p_mago_2->nome);
  }
  else if((p_mago_2->PV) <= 0){
    printf("Partita finita, vince indiscusso "ciano"%s"bianco"\n", p_mago_1->nome);
  }

  elimina_mazzo(p_mago_1);
  elimina_mazzo(p_mago_2);

}

static void pesca(struct Mago *p_mago){
  int i = 0;
  struct Carta *p_temp = p_mago->p_prima_carta;
  for ( i = 0; i < 6; i++) {
    if ((p_mago->mano[i])== NULL) {
      if ((p_mago->p_prima_carta)==(p_mago->p_ultima_carta)) {
        p_mago->mano[i] = p_mago->p_prima_carta;
        p_mago->p_prima_carta = NULL;
        p_mago->p_ultima_carta = NULL;
        printf("Hai pescato l'ultima carta. Alla fine del turno avversario la patita finirà \a\n" );
      }
      else{
        while ((p_temp->p_carta_succ) != NULL) {
          if(p_temp->p_carta_succ == (p_mago->p_ultima_carta)){
            p_mago->mano[i] = p_mago->p_ultima_carta;
            p_temp->p_carta_succ = NULL;
            p_mago->p_ultima_carta = p_temp;
          }
          else{
            p_temp = p_temp->p_carta_succ;
          }
        }
      }
      break;
    }
  }
  if( i == 6 ){
    if ((p_mago->p_prima_carta)==(p_mago->p_ultima_carta)) {
      free(p_mago->p_ultima_carta);
      p_mago->p_prima_carta = NULL;
      p_mago->p_ultima_carta = NULL;
      printf("Ultima carta bruciata, hai la mano piena. Alla fine del turno avversario la patita finirà \a\n" );
    }
    else{
      while ((p_temp->p_carta_succ) != NULL) {
        if((p_temp->p_carta_succ) == (p_mago->p_ultima_carta)){
          free(p_mago->p_ultima_carta);
          p_temp->p_carta_succ = NULL;
          p_mago->p_ultima_carta = p_temp;
          printf("Carta bruciata, hai la mano piena \a\n");
        }
        else{
          p_temp = p_temp->p_carta_succ;
        }
      }
    }
  }
}
static void gioca_posiziona(struct Mago *p_mago_attacco, struct Mago *p_mago_difesa, int*posiziona){
  double k,j,a;
  if (((p_mago_attacco->mano[0]) == NULL) && ((p_mago_attacco->mano[1]) == NULL) && ((p_mago_attacco->mano[2]) == NULL) && ((p_mago_attacco->mano[3]) == NULL)&& ((p_mago_attacco->mano[4]) == NULL)&& ((p_mago_attacco->mano[5]) == NULL) ){
    printf("Non ci sono carte nella tua mano \a\n");
    *posiziona = 0;
  }
  else{
    printf(""blu"Scegli quale carte della mano giocare/posizionare"bianco"\n");
    stampa_mano(p_mago_attacco);
    printf("Proprio campo:\n");
    stampa_campo(p_mago_attacco);
    printf("Campo avversario:\n");
    stampa_campo(p_mago_difesa);
    scanf("%lf", &k );
    stdin=freopen(NULL,"r",stdin);
    while((((int)k<1) || ((int)k>6)) || ((p_mago_attacco->mano[((int)k-1)]) == NULL)){
      if (((int)k<1) || ((int)k>6)) {
        printf("Numero errato, scegli \a\n");
        stampa_mano(p_mago_attacco);
        scanf("%lf", &k );
        stdin=freopen(NULL,"r",stdin);
      }
      else{
        printf("Non hai una carte in quella posizione scegline un'altra \a\n");
        stampa_mano(p_mago_attacco);
        scanf("%lf", &k );
        stdin=freopen(NULL,"r",stdin);
      }
    }
    if ((p_mago_attacco->mano[((int)k-1)])->Tipo == 1) {
      if (((p_mago_attacco->campo[0]) != NULL) && ((p_mago_attacco->campo[1]) != NULL) && ((p_mago_attacco->campo[2]) != NULL) && ((p_mago_attacco->campo[3]) != NULL)) {
           printf("Il campo è pieno, non puoi posizionare un'altra creatura. \a\n");
           *posiziona = 0;
      }
      else{
        printf(""blu"Scegli dove posizionare la carta"bianco"\n");
        stampa_campo(p_mago_attacco);
        scanf("%lf", &j );
        stdin=freopen(NULL,"r",stdin);
        while((((int)j<1) || ((int)j>4)) || ((p_mago_attacco->campo[((int)j-1)]) != NULL)){
          if (((int)j<1) || ((int)j>4)) {
            printf("Numero errato, scegli tra \a\n");
            stampa_campo(p_mago_attacco);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
          else{
            printf("Hai una carta in quella posizione, scegli tra \a\n");
            stampa_campo(p_mago_attacco);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
        }
        p_mago_attacco->campo[((int)j-1)] = (p_mago_attacco->mano[((int)k-1)]);
        p_mago_attacco->mano[((int)k-1)] = NULL;
      }
    }else if ((p_mago_attacco->mano[((int)k-1)])->Tipo == 2){
      if ((((p_mago_difesa->campo[0]) == NULL) && ((p_mago_difesa->campo[1]) == NULL) && ((p_mago_difesa->campo[2]) == NULL) && ((p_mago_difesa->campo[3]) == NULL))) {
        printf("Nessuna carta nel campo avversario, carta bruciata.\n");
        free(p_mago_attacco->mano[((int)k-1)]);
        p_mago_attacco->mano[((int)k-1)] = NULL;
      }
      else{
        printf(""blu"Scegli il bersaglio nel campo nemico"bianco"\n");
        stampa_campo(p_mago_difesa);
        scanf("%lf", &j );
        stdin=freopen(NULL,"r",stdin);
        while((((int)j<1) || ((int)j>4)) || ((p_mago_difesa->campo[((int)j-1)]) == NULL)){
          if (((int)j<1) || ((int)j>4)) {
            printf("Numero errato, scegli tra\a\n");
            stampa_campo(p_mago_difesa);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
          else{
           printf("Nessuna carta in quella posizione scegli tra \a\n");
           stampa_campo(p_mago_difesa);
           scanf("%lf", &j );
           stdin=freopen(NULL,"r",stdin);
         }
       }
       printf(""ciano"%s"bianco" ha eliminato la carta di "ciano"%s"bianco"\n", (p_mago_attacco->nome), (p_mago_difesa->nome) );
       free(p_mago_attacco->mano[((int)k-1)]);
       free(p_mago_difesa->campo[((int)j-1)]);
       p_mago_attacco->mano[((int)k-1)] = NULL;
       p_mago_difesa->campo[((int)j-1)] = NULL;
      }
  }else if ((p_mago_attacco->mano[((int)k-1)])->Tipo == 3){
    printf("Attacchi "ciano"%s"bianco" direttamente " blu "[1]" bianco" oppure una sua creatura " blu "[2]" bianco"?\n", (p_mago_difesa->nome) );
    scanf("%lf", &a);
    stdin=freopen(NULL,"r",stdin);
    while (((int)a != 1) && ((int)a != 2)) {
      printf("Scegliere un numero corretto : ");
      scanf("%lf", &a);
      stdin=freopen(NULL,"r",stdin);
    }
    if(a==1){
      (p_mago_difesa->PV) -= ((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura);
      printf("I PV di "ciano"%s"bianco" sono scesi ad "magenta"%.2lf"bianco"\n",(p_mago_difesa->nome), (p_mago_difesa->PV));
      free(p_mago_attacco->mano[((int)k-1)]);
      p_mago_attacco->mano[((int)k-1)] = NULL;
    }else if(a == 2){
      if ((((p_mago_difesa->campo[0]) == NULL) && ((p_mago_difesa->campo[1]) == NULL) && ((p_mago_difesa->campo[2]) == NULL) && ((p_mago_difesa->campo[3]) == NULL))) {
        printf("Nessuna carta nel campo avversario, carta bruciata.\n");
        free(p_mago_attacco->mano[((int)k-1)]);
        p_mago_attacco->mano[((int)k-1)] = NULL;
      }
      else{
        printf(""blu"Scegli il bersaglio nel campo nemico"bianco"\n");
        stampa_campo(p_mago_difesa);
        scanf("%lf", &j );
        stdin=freopen(NULL,"r",stdin);
        while((((int)j<1) || ((int)j>4)) || ((p_mago_difesa->campo[((int)j-1)]) == NULL)){
          if (((int)j<1) || ((int)j>4)) {
            printf("Numero errato, scegli tra \a\n");
            stampa_campo(p_mago_difesa);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
          else{
           printf("Nessuna carta in quella posizione scegli tra \a\n");
           stampa_campo(p_mago_difesa);
           scanf("%lf", &j );
           stdin=freopen(NULL,"r",stdin);
         }
       }
       if( (((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura)-((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura)) <= 0){
         printf("Hai eliminato la carta di "ciano"%s"bianco"\n", (p_mago_difesa->nome) );
         free(p_mago_attacco->mano[((int)k-1)]);
         free(p_mago_difesa->campo[((int)j-1)]);
         p_mago_attacco->mano[((int)k-1)] = NULL;
         p_mago_difesa->campo[((int)j-1)] = NULL;
       }else{
         ((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura) -= ((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura);
         printf("Il mostro di "ciano"%s"bianco" ha ora vita di "magenta"%.2lf"bianco"\n", p_mago_difesa->nome , (p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura );
         free(p_mago_attacco->mano[((int)k-1)]);
         p_mago_attacco->mano[((int)k-1)] = NULL;
       }
      }
    }
  }
  else if ((p_mago_attacco->mano[((int)k-1)])->Tipo == 4){ //cura
    if (((p_mago_attacco->campo[0]) == NULL) && ((p_mago_attacco->campo[1]) == NULL) && ((p_mago_attacco->campo[2]) == NULL) && ((p_mago_attacco->campo[3]) == NULL)) {
      (p_mago_attacco->PV) += ((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura);
      free(p_mago_attacco->mano[((int)k-1)]);
      p_mago_attacco->mano[((int)k-1)] = NULL;
      printf("Non ci sono Creature nel tuo campo, ti curi direttamente. PV = "magenta"%.2lf"bianco" \n", p_mago_attacco->PV);
    }
    else{
      printf(""ciano"%s"bianco", ti curi direttamente" blu "[1]" bianco" oppure una tua creatura " blu "[2]" bianco"?\n", (p_mago_attacco->nome) );
      scanf("%lf", &a);
      stdin=freopen(NULL,"r",stdin);
      while (((int)a != 1) && ((int)a != 2)) {
        printf("Scegliere un numero corretto : ");
        scanf("%lf", &a);
        stdin=freopen(NULL,"r",stdin);
      }
      if (a == 1) {
        (p_mago_attacco->PV) += ((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura);
        free(p_mago_attacco->mano[((int)k-1)]);
        p_mago_attacco->mano[((int)k-1)] = NULL;
        printf("I tuoi PV ora sono = "magenta"%.2lf"bianco" \n", p_mago_attacco->PV);
      }
      else if( a == 2){
        printf(""blu"Scegli la carta da curare"bianco"\n");
        stampa_campo(p_mago_attacco);
        scanf("%lf", &j );
        stdin=freopen(NULL,"r",stdin);
        while((((int)j<1) || ((int)j>4)) || ((p_mago_attacco->campo[((int)j-1)]) == NULL)){
          if (((int)j<1) || ((int)j>4)) {
            printf("Numero errato, scegli tra \a\n");
            stampa_campo(p_mago_attacco);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
          else{
            printf("Non hai una carte in quella posizione, scegli tra \a\n");
            stampa_campo(p_mago_attacco);
            scanf("%lf", &j );
            stdin=freopen(NULL,"r",stdin);
          }
        }
        ((p_mago_attacco->campo[((int)j-1)])->punti_vita_danno_cura)+=((p_mago_attacco->mano[((int)k-1)])->punti_vita_danno_cura);
        free(p_mago_attacco->mano[((int)k-1)]);
        p_mago_attacco->mano[((int)k-1)] = NULL;
        printf("I PV della creatura ora sono = "magenta"%.2lf"bianco" \n", ((p_mago_attacco->campo[((int)j-1)])->punti_vita_danno_cura));
      }
    }
   }
  }
}
static void attacca(struct Mago *p_mago_attacco, struct Mago *p_mago_difesa, int *attacca){
  double k,j,a;
  if (((p_mago_attacco->campo[0]) == NULL) && ((p_mago_attacco->campo[1]) == NULL) && ((p_mago_attacco->campo[2]) == NULL) && ((p_mago_attacco->campo[3]) == NULL)) {
    printf("Hai il campo vuoto\n");
    *attacca = 0;
  }
  else{
    printf(""blu"Scegli quale creature debba attaccare."bianco"\n" );
    stampa_campo(p_mago_attacco);
    scanf("%lf", &k );
    stdin=freopen(NULL,"r",stdin);
    while((((int)k<1) || ((int)k>4)) || ((p_mago_attacco->campo[((int)k-1)]) == NULL)){
      if (((int)k<1) || ((int)k>4)) {
        printf("Numero errato, scegli tra \a\n");
        stampa_campo(p_mago_attacco);
        scanf("%lf", &k );
        stdin=freopen(NULL,"r",stdin);
      }
      else{
        printf("Non hai una carte in quella posizione, scegli tra \a\n");
        stampa_campo(p_mago_attacco);
        scanf("%lf", &k );
        stdin=freopen(NULL,"r",stdin);
      }
    }
    if (((p_mago_difesa->campo[0]) == NULL) && ((p_mago_difesa->campo[1]) == NULL) && ((p_mago_difesa->campo[2]) == NULL) && ((p_mago_difesa->campo[3]) == NULL)) {
      (p_mago_difesa->PV) -= ((p_mago_attacco->campo[((int)k-1)])->punti_vita_danno_cura);
      printf("Il campo avversario è vuoto, attacchi direttamente "ciano"%s"bianco", ora i suoi PV sono "magenta"%.2lf"bianco"\n", (p_mago_difesa->nome), (p_mago_difesa->PV) );
    }
    else{
      int num_creature_att = 0;
      int num_creature_dif = 0;
      for (int i = 0; i < 4; i++) {
        if((p_mago_attacco->campo[i]) != NULL){
          num_creature_att++;
        }
        if((p_mago_difesa->campo[i]) != NULL){
          num_creature_dif++;
        }
      }
      if (num_creature_att > num_creature_dif) {
        printf("Attacchi "ciano"%s"bianco" direttamente " blu "[1]" bianco" oppure una sua creatura " blu "[2]" bianco"?\n", (p_mago_difesa->nome) );
        stampa_campo(p_mago_difesa);
        scanf("%lf", &a );
        stdin=freopen(NULL,"r",stdin);
        while (((int)a!= 1)&&((int)a!=2)) {
          printf("Scegli un numero valido \a\n");
          stampa_campo(p_mago_difesa);
          scanf("%lf", &a );
          stdin=freopen(NULL,"r",stdin);
        }
        if (a == 1) {
          (p_mago_difesa->PV) -= ((p_mago_attacco->campo[((int)k-1)])->punti_vita_danno_cura);
          printf("Hai attaccato direttamente "ciano"%s"bianco" ora i suoi PV sono "magenta"%.2lf"bianco" \n", (p_mago_difesa->nome), (p_mago_difesa->PV));
        }
        else if (a == 2) {
          printf(""blu"Quale carta vuoi attaccare?"bianco"\n" );
          stampa_campo(p_mago_difesa);
          scanf("%lf", &j);
          stdin=freopen(NULL,"r",stdin);
          while((((int)j<1) || ((int)j>4)) || ((p_mago_difesa->campo[((int)j-1)]) == NULL)){
            if (((int)j<1) || ((int)j>4)) {
              printf("Numero errato, scegli tra \a\n");
              stampa_campo(p_mago_difesa);
              scanf("%lf", &j );
              stdin=freopen(NULL,"r",stdin);
            }
            else{
              printf("Nessuna carta selezionata nel campo avversario, scegli tra \a\n");
              stampa_campo(p_mago_difesa);
              scanf("%lf", &j );
              stdin=freopen(NULL,"r",stdin);
            }
          }
          ((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura)-=((p_mago_attacco->campo[((int)k-1)])->punti_vita_danno_cura);
          if (((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura) <= 0) {
            printf("Hai eliminato la carta di "ciano"%s"bianco"\n", (p_mago_difesa->nome) );
            free(p_mago_difesa->campo[((int)j-1)]);
            p_mago_difesa->campo[((int)j-1)] = NULL;
          }
          else{
            printf("La vita della carta attaccata ora è "magenta"%.2lf"bianco" \n", ((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura) );
          }
        }
      }
      else{
          printf(""blu"Quale carta vuoi attaccare?"bianco"\n" );
          stampa_campo(p_mago_difesa);
          scanf("%lf", &j);
          stdin=freopen(NULL,"r",stdin);
          while((((int)j<1) || ((int)j>4)) || ((p_mago_difesa->campo[((int)j-1)]) == NULL)){
            if (((int)j<1) || ((int)j>4)) {
              printf("Numero errato, scegli tra \a\n");
              stampa_campo(p_mago_difesa);
              scanf("%lf", &j );
              stdin=freopen(NULL,"r",stdin);
            }
            else{
              printf("Nessuna carta selezionata nel campo avversario, scegli tra \a\n");
              stampa_campo(p_mago_difesa);
              scanf("%lf", &j );
              stdin=freopen(NULL,"r",stdin);
            }
          }
          ((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura)-=((p_mago_attacco->campo[((int)k-1)])->punti_vita_danno_cura);
          if (((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura) <= 0) {
            printf("Hai eliminato la carta di "ciano"%s"bianco"\n", (p_mago_difesa->nome) );
            free(p_mago_difesa->campo[((int)j-1)]);
            p_mago_difesa->campo[((int)j-1)] = NULL;
          }
          else{
            printf("La vita della carta attaccata ora è "magenta"%.2lf"bianco" \n", ((p_mago_difesa->campo[((int)j-1)])->punti_vita_danno_cura) );
          }
        }
    }
    *attacca = 1;
  }
}
static void passa(int*giocatore, int*pescata, int*posiziona, int*attacca, int*pv){
  if (*giocatore == 0) {
    *pv = 0;
    *pescata = 0;
    *posiziona = 0;
    *attacca = 0;
    *giocatore = 1;
  }
  else if (*giocatore == 1) {
    *pv = 0;
    *pescata = 0;
    *posiziona = 0;
    *attacca = 0;
    *giocatore = 0;
  }
}
static void stampa_campo(struct Mago *p_mago){
  printf("██████████████"blu"[1]"bianco"█████████████   ██████████████"blu"[2]"bianco"█████████████   ██████████████"blu"[3]"bianco"█████████████   ██████████████"blu"[4]"bianco"█████████████\n");
  printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");
for (int i = 0; i <4 ; i++) { // terza riga
  if (p_mago->campo[i] == NULL) { //se nullo
      printf("██                          ██");
  }else{
    if (((p_mago->campo[i])->Tipo) == 1) { //creatura
      printf("██                          ██");
    }
    else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
      printf("██       "rosso"     ▄▄▄     "bianco"      ██");
    }
    else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
      printf("██           "rosso"  +*   "bianco"        ██");
    }
    else if (((p_mago->campo[i])->Tipo) == 4) { // cura
      printf("██                          ██");
    }
  }
    printf("   ");
  }
  puts("");

  for (int i = 0; i <4 ; i++) { // quarta riga
    if (p_mago->campo[i] == NULL) { //se nullo
        printf("██  ▄▄    ▄         ╓▄  ▄╕  ██");
    }else{
      if (((p_mago->campo[i])->Tipo) == 1) { //creatura
        if (p_mago->Classe == 1) { //tenebre
          printf("██         "rosso"▄██████▄"bianco"         ██");
        }
        else if (p_mago->Classe == 2) { // vita
          printf("██        "verde"(\\   _  /)"bianco"        ██");
        }
        else if (p_mago->Classe == 3) { // luce
          printf("██"giallo"__━_*__┓ ╭¬¬¬¬¬¬¬━━━━╮    "bianco"██");
        }
      }
      else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
        printf("██         "rosso"   ▐█▌   "bianco"        ██");
      }
      else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
        printf("██             ▌            ██");
      }
      else if (((p_mago->campo[i])->Tipo) == 4) { // cura
        printf("██            "verde"███"bianco"           ██");
      }
    }
      printf("   ");
    }
    puts("");

    for (int i = 0; i <4 ; i++) { // quinta riga
      if (p_mago->campo[i] == NULL) { //se nullo
          printf("██  ███   █  █▌  █▌ ▐█  █▌  ██");
      }else{
        if (((p_mago->campo[i])->Tipo) == 1) { //creatura
          if (p_mago->Classe == 1) { //tenebre
            printf("██        "rosso"▐█▌████▐█▌"bianco"        ██");
          }
          else if (p_mago->Classe == 2) { // vita
            printf("██        "verde"( \\ ( )/ )"bianco"        ██");
          }
          else if (p_mago->Classe == 3) { // luce
            printf("██"giallo"__━━___┗┓|:¬¬¬¬¬¬:^━━━━━^ "bianco"██");
          }
        }
        else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
          printf("██         "rosso"   ▐█▌   "bianco"        ██");
        }
        else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
          printf("██      "nero_chiaro"     ▐███      "bianco"     ██");
        }
        else if (((p_mago->campo[i])->Tipo) == 4) { // cura
          printf("██            "verde"███"bianco"           ██");
        }
      }
        printf("   ");
      }
      puts("");

      for (int i = 0; i <4 ; i++) { // sesta riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██  █▌▀█▄ █  █▌  █▌ ▐█  █▌  ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██         "rosso"█▌ ██ ▐█"bianco"         ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██        "verde"(__    __)"bianco"        ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██"giallo"_━━*___━┗|:¬¬¬¬¬¬|｡0‿‿ 0｡|"bianco"██");
            }
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██        "rosso"   ▄███▄   "bianco"       ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██    "nero_chiaro"     ▄███████▄    "bianco"    ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██        "verde"███████████"bianco"       ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i <4 ; i++) { // sett riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██  █▌  ███  █▌  █▌ ▐█  █▌  ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██          "rosso"▀████▀"bianco"          ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██           "verde"/   \\"bianco"          ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██"giallo"_━━___*━━╰O━O━━━━╰--O-O--╯"bianco"██");
            }
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██       "rosso"  ▀▀ "bianco"║ ║ "rosso"▀▀  "bianco"      ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██      "nero_chiaro"  ▐█████████▌    "bianco"   ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██            "verde"███"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i <4 ; i++) { // ottava riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██  ▀▀   ▀▀  ▀▀▀▀▀▀ ╙▀  ▀╛  ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██           "rosso"▌▐▌▐"bianco"           ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██          "verde"/_____\\"bianco"         ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██                          ██");
            }
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██            ║║║           ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██     "nero_chiaro"   ▐█████████▌   "bianco"    ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██            "verde"███"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i <4 ; i++) { // nona riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██                          ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██           "rosso"▀▀▀▀"bianco"           ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██                          ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██                          ██");
            }
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██            │║│           ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██      "nero_chiaro"   ▀███████▀   "bianco"     ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██            "verde"▀▀▀"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");//deci riga
        for (int i = 0; i <4 ; i++) { // 11 riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██            NULL          ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            printf("██     "blu_chiaro"Genere:"magenta" Creatura"bianco"     ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██ "blu_chiaro"Genere:"magenta" Elimina creatura"bianco" ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██ "blu_chiaro"Genere:"magenta" Attacco generale"bianco" ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██       "blu_chiaro"Genere:"magenta" Cura"bianco"       ██");
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n"); //12 riga

        for (int i = 0; i <4 ; i++) { // 13 riga
        if (p_mago->campo[i] == NULL) { //se nullo
            printf("██            NULL          ██");
        }else{
          if (((p_mago->campo[i])->Tipo) == 1) { //creatura
            printf("██          "blu_chiaro"PV:"magenta"%5.2lf"bianco"        ██", (p_mago->campo[i])->punti_vita_danno_cura);
          }
          else if (((p_mago->campo[i])->Tipo) == 2) { // uccidi creatura
            printf("██     "magenta"Scegli bersaglio "bianco"    ██");
          }
          else if (((p_mago->campo[i])->Tipo) == 3) { // attacco generale
            printf("██  "blu_chiaro"Infliggi danno:"magenta"%5.2lf "bianco"   ██", (p_mago->campo[i])->punti_vita_danno_cura);
          }
          else if (((p_mago->campo[i])->Tipo) == 4) { // cura
            printf("██        "blu_chiaro"Bonus:"magenta"%5.2lf   "bianco"    ██", (p_mago->campo[i])->punti_vita_danno_cura);
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");
        puts("");
}
static void stampa_mano(struct Mago *p_mago){
  printf("██████████████"blu"[1]"bianco"█████████████   ██████████████"blu"[2]"bianco"█████████████   ██████████████"blu"[3]"bianco"█████████████   ██████████████"blu"[4]"bianco"█████████████   ██████████████"blu"[5]"bianco"█████████████   ██████████████"blu"[6]"bianco"█████████████\n");
  printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");
for (int i = 0; i < 6; i++) { // terza riga
  if (p_mago->mano[i] == NULL) { //se nullo
      printf("██                          ██");
  }else{
    if (((p_mago->mano[i])->Tipo) == 1) { //creatura
      printf("██                          ██");
    }
    else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
      printf("██       "rosso"     ▄▄▄     "bianco"      ██");
    }
    else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
      printf("██           "rosso"  +*   "bianco"        ██");
    }
    else if (((p_mago->mano[i])->Tipo) == 4) { // cura
      printf("██                          ██");
    }
  }
    printf("   ");
  }
  puts("");

  for (int i = 0; i < 6; i++) { // quarta riga
    if (p_mago->mano[i] == NULL) { //se nullo
        printf("██  ▄▄    ▄         ╓▄  ▄╕  ██");
    }else{
      if (((p_mago->mano[i])->Tipo) == 1) { //creatura
        if (p_mago->Classe == 1) { //tenebre
          printf("██         "rosso"▄██████▄"bianco"         ██");
        }
        else if (p_mago->Classe == 2) { // vita
          printf("██        "verde"(\\   _  /)"bianco"        ██");
        }
        else if (p_mago->Classe == 3) { // luce
          printf("██"giallo"__━_*__┓ ╭¬¬¬¬¬¬¬━━━━╮    "bianco"██");
        }
      }
      else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
        printf("██         "rosso"   ▐█▌   "bianco"        ██");
      }
      else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
        printf("██             ▌            ██");
      }
      else if (((p_mago->mano[i])->Tipo) == 4) { // cura
        printf("██            "verde"███"bianco"           ██");
      }
    }
      printf("   ");
    }
    puts("");

    for (int i = 0; i < 6; i++) { // quinta riga
      if (p_mago->mano[i] == NULL) { //se nullo
          printf("██  ███   █  █▌  █▌ ▐█  █▌  ██");
      }else{
        if (((p_mago->mano[i])->Tipo) == 1) { //creatura
          if (p_mago->Classe == 1) { //tenebre
            printf("██        "rosso"▐█▌████▐█▌"bianco"        ██");
          }
          else if (p_mago->Classe == 2) { // vita
            printf("██        "verde"( \\ ( )/ )"bianco"        ██");
          }
          else if (p_mago->Classe == 3) { // luce
            printf("██"giallo"__━━___┗┓|:¬¬¬¬¬¬:^━━━━━^ "bianco"██");
          }
        }
        else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
          printf("██         "rosso"   ▐█▌   "bianco"        ██");
        }
        else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
          printf("██       "nero_chiaro"    ▐███      "bianco"     ██");
        }
        else if (((p_mago->mano[i])->Tipo) == 4) { // cura
          printf("██            "verde"███"bianco"           ██");
        }
      }
        printf("   ");
      }
      puts("");

      for (int i = 0; i < 6; i++) { // sesta riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██  █▌▀█▄ █  █▌  █▌ ▐█  █▌  ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██         "rosso"█▌ ██ ▐█"bianco"         ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██        "verde"(__    __)"bianco"        ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██"giallo"_━━*___━┗|:¬¬¬¬¬¬|｡0‿‿ 0｡|"bianco"██");
            }
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██        "rosso"   ▄███▄   "bianco"       ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██      "nero_chiaro"   ▄███████▄     "bianco"   ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██        "verde"███████████"bianco"       ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i < 6; i++) { // sett riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██  █▌  ███  █▌  █▌ ▐█  █▌  ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██          "rosso"▀████▀"bianco"          ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██           "verde"/   \\"bianco"          ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██"giallo"_━━___*━━╰O━O━━━━╰--O-O--╯"bianco"██");
            }
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██       "rosso"  ▀▀ "bianco"║ ║ "rosso"▀▀  "bianco"      ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██     "nero_chiaro"   ▐█████████▌    "bianco"   ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██            "verde"███"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i < 6; i++) { // ottava riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██  ▀▀   ▀▀  ▀▀▀▀▀▀ ╙▀  ▀╛  ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██           "rosso"▌▐▌▐"bianco"           ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██          "verde"/_____\\"bianco"         ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██                          ██");
            }
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██            ║║║           ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██    "nero_chiaro"    ▐█████████▌ "bianco"      ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██            "verde"███"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        for (int i = 0; i < 6; i++) { // nona riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██                          ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            if (p_mago->Classe == 1) { //tenebre
              printf("██           "rosso"▀▀▀▀"bianco"           ██");
            }
            else if (p_mago->Classe == 2) { // vita
              printf("██                          ██");
            }
            else if (p_mago->Classe == 3) { // luce
              printf("██                          ██");
            }
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██            │║│           ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██      "nero_chiaro"   ▀███████▀   "bianco"     ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██            "verde"▀▀▀"bianco"           ██");
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");//deci riga
        for (int i = 0; i < 6; i++) { // 11 riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██            NULL          ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            printf("██     "blu_chiaro"Genere:"magenta" Creatura"bianco"     ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██ "blu_chiaro"Genere:"magenta" Elimina creatura"bianco" ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██ "blu_chiaro"Genere:"magenta" Attacco generale"bianco" ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██       "blu_chiaro"Genere:"magenta" Cura"bianco"       ██");
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n"); //12 riga

        for (int i = 0; i < 6; i++) { // 13 riga
        if (p_mago->mano[i] == NULL) { //se nullo
            printf("██            NULL          ██");
        }else{
          if (((p_mago->mano[i])->Tipo) == 1) { //creatura
            printf("██          "blu_chiaro"PV:"magenta"%5.2lf"bianco"        ██", (p_mago->mano[i])->punti_vita_danno_cura);
          }
          else if (((p_mago->mano[i])->Tipo) == 2) { // uccidi creatura
            printf("██     "magenta"Scegli bersaglio "bianco"    ██");
          }
          else if (((p_mago->mano[i])->Tipo) == 3) { // attacco generale
            printf("██  "blu_chiaro"Infliggi danno:"magenta"%5.2lf "bianco"   ██", (p_mago->mano[i])->punti_vita_danno_cura);
          }
          else if (((p_mago->mano[i])->Tipo) == 4) { // cura
            printf("██        "blu_chiaro"Bonus:"magenta"%5.2lf   "bianco"    ██", (p_mago->mano[i])->punti_vita_danno_cura);
          }
        }
          printf("   ");
        }
        puts("");

        printf("██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████   ██████████████████████████████\n");
        puts("");
}

void termina_gioco( int *termina , double *reimposta , struct Mago *p_mago_1, struct Mago *p_mago_2, int numero_carte){
  system("clear");
  printf("Sicuro di voler terminare il gioco? Premi " blu "[1]" bianco" per si e " blu "[2]" bianco" per no: ");
  scanf("%d", termina);
  stdin=freopen(NULL,"r",stdin);
  while ((*termina)!=1 && (*termina)!=2) {
    printf("Immetti un numero valido:\a ");
    scanf("%d", termina);
    stdin=freopen(NULL,"r",stdin);
  }
   if (((int)*termina) == 1) {
     system("clear");
     elimina_mazzo(p_mago_1);
     elimina_mazzo(p_mago_2);
     titolo();
     printf("\n");
     printf("                                                      \"THE END\" \n");
     crediti();
   }else if(((int)*termina) == 2){
     if ((*reimposta) == 2) {
       elimina_mazzo(p_mago_1);
       elimina_mazzo(p_mago_2);
       printf("Devi impostare il gioco prima di poter combattere\n");
       *reimposta = 1;
     }
   }
}



