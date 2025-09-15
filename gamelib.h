//DEFINIZIONE COLORI
#define rosso "\x1b[31m"
#define blu "\x1b[34m"
#define bianco "\x1b[97m"
#define giallo "\x1b[33m"
#define verde "\x1b[32m"
#define blu_chiaro "\x1b[94m"
#define magenta "\x1b[35m"
#define ciano "\x1b[36m"
#define nero_chiaro "\x1b[90m"

typedef enum Classe_Mago{
  Tenebre = 1,
  Vita,
  Luce
} Classe_mago;

typedef enum Tipo_Carta{
  Creatura = 1,
  Rimuovi_creatura,
  Infliggi_danno,
  Guarisci_danno
} Tipo_carta;

struct Carta{
  Tipo_carta Tipo;
  double punti_vita_danno_cura;
  struct Carta *p_carta_succ;
};

struct Mago{
  char nome[25];
  double PV;
  Classe_mago Classe;
  struct Carta *p_prima_carta; //ultima mazzo
  struct Carta *p_ultima_carta; //primo mazzo
  struct Carta *mano[6];
  struct Carta *campo[4];
};

// DICHIARAZIONI FUNZIONE MAIN
void imposta_gioco(struct Mago *p_mago_1, struct Mago *p_mago_2, int* n);

void dealloca(struct Mago *p_mago_1, struct Mago *p_mago_2);

void combatti(struct Mago *p_mago_1, struct Mago *p_mago_2, int numero_carte);

void termina_gioco(  int *termina , double *reimposta , struct Mago *p_mago_1, struct Mago *p_mago_2, int num_carte);

void crediti(void);

void storia(void);

void titolo(void);



