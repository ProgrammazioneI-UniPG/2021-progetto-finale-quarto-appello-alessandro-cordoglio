#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gamelib.h"
//dichiarazione di variabili
int ch;
int go;
int sc;
int scelta;
int perc_room;
int quest;
int imp;
int i,j;
int num_p;
time_t t;
int quest;
int num_q;
int quest=0;
int playerstanza;
//dichiarazione dei puntatori alle struct
struct Stanza* new_stage;
struct Stanza* stanza_inizio;
struct Giocatore* player;
struct Stanza* stanzabotola;
struct Stanza* list_s;
struct Stanza* new_stage;
//array che fanno riferimento alle struct
const char* Nome_giocatore[]={"rosso","giallo","blu","verde","viola","nero","marrone","arancione","rosa","bianco"};
const char* Stato_giocatore[]={"astronauta","impostore","assassinato","defenestrato"};
const char* Tipo_stanza[]={"vuota", "quest_semplice", "quest_complicata", "botola"};

//funzione conclusione
static int fine(){
  int astronauti=0;
  int impostori=0;
  int f=0;
  ///calcolo del numero degli astronauti e degli impostori
  for(int turno=0;turno<num_p && f==0;turno++){
  for(int i=0;i<num_p;i++){
    if(player[i].stato==0){
      astronauti++;
    }
    if(player[i].stato==1){
      impostori++;
    }
  }
  //controllo delle condizioni di vittoria di entrambe le squadre
  if(astronauti==0){
    f=1;
    termina_gioco();
    system("clear");
    printf("\n\t    VITTORIA IMPOSTORI");
    printf("\nPremi invio per ritornare al menù");
    while(getchar() != '\n' && getchar() != EOF);

  }
  if(impostori==0 || quest==num_q){
    f=1;
    termina_gioco();
    system("clear");
    printf("\n\t    VITTORIA ASTRONAUTI");
    printf("\nPremi invio per ritornare al menù");
    while(getchar() != '\n' && getchar() != EOF);

  }
}
return f;
}

//funzione botola
static void usa_botola(int *turni, int turno){
  //controllo che non fa utilizzare la botola se non esistono stanze create
  if (stanza_inizio -> next_room == NULL) {
    printf("\nnon puoi usare la botola nella stanza iniziale\n");
  }

int num_b = 0;
int num_s = 0;
int cambio;//variabile
int i=0;
  //variabile che fa riferimento a stanza a cui sono assegnate le varie stanze create
struct Stanza *st = list_s;

  //se la stanza è di tipo botola allora aumenta il numero di botole
do{
    num_s++;
    if(st->tipo == 3){
      num_b++;
    }
    st=st->next_room;
  }while(st!=NULL);

struct Stanza *botole[num_b];
st = list_s;

do{
  if(st->tipo ==3 ){
    botole[i]=st;
    i++;
    }
  st=st->next_room;
}while(st!=NULL);

  //se le botole sono maggiori di uno allora il giocatore si teletrasporterà in una stanza botola casuale
if(num_b>1){
      cambio=rand()%num_b;
      for(i=0; i<num_b; i++){
        if(i==cambio){
      player[turni[turno]].pstanza=botole[i]; //il giocatore viene portato nella stanza con botola
      printf("sei in una stanza con botola\n" );
        }
      }
    }

  else if(num_b==1&&num_s>1){
    cambio=rand()%num_s;
    st = list_s; i=0;
    while(st!=NULL){
    	if(i == cambio){
		player[turni[turno]].pstanza=st;
		printf("\nsei in una stanza di tipo %s",Tipo_stanza[player[turni[turno]].pstanza->tipo]); //il giocatore viene portato in una stanza casuale dalla lista
		break;
	}
	i++;
	st=st->next_room;
    }
  }
}

//termina gioco
void termina_gioco(){
  if(list_s!=NULL){
    do{
      list_s=list_s->next_room;
      free(list_s);
    }while(list_s!=NULL);
  }
  free(player);
  free(stanza_inizio);
  num_p=0;
  printf("\nMemoria deallocata...\n\n");
}

//funzione avanza
static void avanza(int *turni,int turno){

  struct Stanza* lista=list_s;
  printf("\n Dove vuoi andare?\n" );
  printf(" (1)AVANTI   (2)DESTRA   (3)SINISTRA " );
  scanf("%d", &go );
  while((ch= getchar() !='\n' && ch !=EOF));
  switch (go) {

      case 1:
      if(player[turni[turno]].pstanza->avanti==NULL){
        //creazione delle stanze(A)
        struct Stanza* new_stage = (struct Stanza*) malloc(sizeof(struct Stanza));
        int perc_room=0;
        new_stage->avanti=NULL;
        new_stage->sinistra=NULL;
        new_stage->destra=NULL;
        new_stage->stanza_precedente=NULL;
        new_stage->chiamata_emergenza=FALSE;
        perc_room=rand () %100;
        if(0<=perc_room&&perc_room<=25){
            new_stage->tipo=3;
        }
        if(26<=perc_room&&perc_room<=40){
            new_stage->tipo=2;
        }
        if(41<=perc_room&&perc_room<=70){
            new_stage->tipo=1;
        }
        if(71<=perc_room&&perc_room<=100){
            new_stage->tipo=0;
        }

        //inserimento delle nuove stanze in una lista in memoria(B)
          do{
          if(lista->next_room==NULL){
            lista->next_room=new_stage;
            break;
          }
          lista=lista->next_room;
        }while(lista!=NULL);

         player[turni[turno]].pstanza->avanti = new_stage;
          player[turni[turno]].pstanza=player[turni[turno]].pstanza->avanti;
          printf("\n Ti trovi in una nuova stanza ->AVANTI" );
      }else{
        player[turni[turno]].pstanza=player[turni[turno]].pstanza->avanti;
        printf("\nTi trovi in una stanza esistente ->AVANTI" );}
        break;

      case 2:
      if(player[turni[turno]].pstanza->destra==NULL){
        struct Stanza* new_stage = (struct Stanza*) malloc(sizeof(struct Stanza));
        //(A)
        int perc_room=0;
        new_stage->avanti=NULL;
        new_stage->sinistra=NULL;
        new_stage->destra=NULL;
        new_stage->stanza_precedente=NULL;
        new_stage->chiamata_emergenza=FALSE;
        perc_room=rand () %100;
        if(0<=perc_room&&perc_room<=25){
            new_stage->tipo=3;
        }
        if(26<=perc_room&&perc_room<=40){
            new_stage->tipo=2;
        }
        if(41<=perc_room&&perc_room<=70){
            new_stage->tipo=1;
        }
        if(71<=perc_room&&perc_room<=100){
            new_stage->tipo=0;
        }

        //(B)
          do{
          if(lista->next_room==NULL){
            lista->next_room=new_stage;
            break;
          }
          lista=lista->next_room;
        }while(lista!=NULL);

         player[turni[turno]].pstanza->destra = new_stage;
          player[turni[turno]].pstanza=player[turni[turno]].pstanza->destra;
          printf("\n Ti trovi in una nuova stanza ->DESTRA"  );
      }else{
        player[turni[turno]].pstanza=player[turni[turno]].pstanza->destra;
        printf("\n Ti trovi in una stanza esistente ->DESTRA" );}
        break;

      case 3:
      if(player[turni[turno]].pstanza->sinistra==NULL){
        struct Stanza* new_stage = (struct Stanza*) malloc(sizeof(struct Stanza));
        //(A)
        int perc_room=0;
        new_stage->avanti=NULL;
        new_stage->sinistra=NULL;
        new_stage->destra=NULL;
        new_stage->stanza_precedente=NULL;
        new_stage->chiamata_emergenza=FALSE;
        perc_room=rand () %100;
        if(0<=perc_room&&perc_room<=25){
            new_stage->tipo=3;
        }
        if(26<=perc_room&&perc_room<=40){
            new_stage->tipo=2;
        }
        if(41<=perc_room&&perc_room<=70){
            new_stage->tipo=1;
        }
        if(71<=perc_room&&perc_room<=100){
            new_stage->tipo=0;
        }

        //(B)
          do{
          if(lista->next_room==NULL){
            lista->next_room=new_stage;
            break;
          }
          lista=lista->next_room;
        }while(lista!=NULL);

         player[turni[turno]].pstanza->sinistra = new_stage;
          player[turni[turno]].pstanza=player[turni[turno]].pstanza->sinistra;
          printf("\n Ti trovi in una nuova stanza ->SINISTRA"  );
      }else{
        player[turni[turno]].pstanza=player[turni[turno]].pstanza->sinistra;
        printf("\n Ti trovi in una stanza esistente ->SINISTRA" );}
        break;
      }
}

//funzione sabotaggio
static void sabotaggio(int *turni,int turno){
  player[turni[turno]].pstanza->tipo=0;
  printf("Quest sabotata con successo\n");
}

//esegui quest
static void esegui_quest(int *turni, int turno){
  if (player[turni[turno]].pstanza->tipo==1) {
    quest=quest+1;
  }
  else if (player[turni[turno]].pstanza->tipo==2) {
    quest=quest+2;
  }
  player[turni[turno]].pstanza->tipo=0;

  if (quest==num_q) {
    system("clear");
    printf("HANNO VINTO GLI ASTRONAUTI!" );
    while(getchar() != '\n' && getchar() != EOF);
  } else {
    printf("hai completato %d/%d quest \n", quest, num_q );
  }
}

//chiamata emergenza
static void chiamata_emergenza(int *turni, int turno){
int impostori, astronauti, percentualeI, percentualeA;
  //controllo di quanti impostori/astronauti ci siano nella stanza
for(int i=0;i<num_p;i++){
  if(player[turni[turno]].pstanza==player[i].pstanza && player[i].stato==0){
    astronauti++;
  }
  if(player[turni[turno]].pstanza==player[i].pstanza && player[i].stato==1){
    impostori++;
  }
}
percentualeI=30+(astronauti*20)-(impostori*30);
percentualeA=30+(impostori*20)-(astronauti*30);
int random=0;
random=rand()%100;
int nondef=0;
for(int i=0;i<num_p;i++){
  if(player[turni[turno]].pstanza==player[i].pstanza && player[i].stato==0 && nondef==0){
    if(random<=percentualeA){
      player[i].stato=3;
      printf("\n%s defenestrato: Astronauta\n", Nome_giocatore[player[i].nome]);
      nondef=1;
    }
  }
  if(player[turni[turno]].pstanza==player[i].pstanza && player[i].stato==1 && nondef==0){
    if(random>=(random-percentualeI)){
      player[i].stato=3;
      printf("\n%s defenestrato: Impostore\n", Nome_giocatore[player[i].nome]);
      nondef=1;
    }
  }
}
if(nondef==0){
  printf("\nNon e' stato defenestrato nessuno\n");
}
player[turni[turno]].pstanza->chiamata_emergenza=TRUE;
}

//uccidi Astronauta
static void uccidi_astronauta(int *turni, int turno){
srand((unsigned) time(&t));
int ucciso=0;
int s;
int astrostanza=0;
int astrodietro=0;
int prob=0;
int caso;
  //conteggio degli astronauti nella stanza presente e in quella precedente
for(int i=0;i<num_p;i++){
    if(player[i].pstanza==player[turni[turno]].pstanza && player[i].stato==0){
      astrostanza++;
    }
    if(player[i].pstanza==player[turni[turno]].pstanza->stanza_precedente && player[i].stato==0){
      astrodietro++;
    }
  }
  //if che determina l'assassinato
if(astrostanza>0){
    do{
      for(int i=0;i<num_p && ucciso==0;i++){
        if(player[i].pstanza==player[turni[turno]].pstanza && player[i].stato==0){
          do{
            printf("immetti (1) per uccidere il giocatore %s altrimenti immetti (2) per scegliere un altro nella stanza \n", Nome_giocatore[player[i].nome]);
            scanf("%d", &s);
            if(s==1){
              ucciso=1;
              player[i].stato=2;
              printf("Hai ucciso il giocatore %s ", Nome_giocatore[player[i].nome]);
            }
          }while (s!=1 && s!=2);
        }
      }
    }while(ucciso==0);
  astrostanza--;
   }


prob=rand()%100;
caso=(astrostanza*50)+(astrodietro*20);
if(prob<caso){
  player[turni[turno]].stato=3;
  printf(" ti hanno scoperto, sei stato defenestrato\n");
}else{
  printf("non sei stato scoperto\n");
}
}

//inzio funzione per settare il gioco
int imposta_gioco(){
//menù di immissione dei giocatori
srand((unsigned)time(&t));
  do {
    printf("\nINSERISCI IL NUMERO DI GIOCATORI:\n");
    scanf("%d",&num_p);
    while(getchar()!='\n');
    if (num_p<4 || num_p>10) {
      printf("!ERRORE DI IMMISSIONE! ci possono essere minimo 4 giocatori e massimo 10.\n");
    }
  } while(num_p<4 || num_p>10);

player=malloc(num_p*sizeof(struct Giocatore));

//assegnazione dei nomi casuali ai giocatori
  for(int i=0;i<num_p;i++){
    player[i].nome=rand()%10;
//for che evita la duplicazione dei nomi
  for (j = 0; j < i; j++) {
    if (player[i].nome == player[j].nome) {
      i--;
    }
  }
}
//inizializzazione dei ruoli
for (i = 0; i <num_p-1; i++) {
  player[i].stato=0;
}
//assegnazione dei ruoli

  //un impostore random se i giocatori sono da 4 a 6
  if (num_p<7 && num_p>3) {
    player[rand()%num_p].stato=1;
    }
  //due impostori random se i giocatori sono da 7 a 8
  else if (num_p<9 && num_p>6) {
    i = 0;
    while (i<2){
      int random = rand()%num_p;
      if(player[random].stato==0){
        player[random].stato=1;
        i++;
      }
    }
  }
  //tre impostori se i giocatori sono da 9 a 10
  else if (num_p<11 && num_p>8) {
    i = 0;
    while (i<3){
      int random = rand()%num_p;
      if(player[random].stato==0){
        player[random].stato=1;
        i++;
      }
    }
  }
//richiesta di immissione delle quest da completare
do {
    printf("\nINSERISCI IL NUMERO DI QUEST DA COMPLETARE PER VINCERE:\n");
    scanf("%d",&num_q);
    while(getchar()!='\n');
    if (num_q<num_p) {
      printf("!ERRORE DI IMMISSIONE! Puoi inserire un numero di quest uguale o maggiore al numero di giocatori.\n");
    }
  } while(num_q<num_p);

//funzione per stampare i giocatori
int stampa_giocatori(){
    printf("\t __________________________________________________________________\n" );
    printf("\t                              LISTA   \n");
    printf("\t                            GIOCATORI \n" );
    printf("\t __________________________________________________________________\n" );
    printf("\n" );
    for (int i = 0; i < num_p; i++) {
      printf("\t\t\t%s", Nome_giocatore[player[i].nome] );
      printf("\t\t         %s\n", Stato_giocatore[player[i].stato] );
    }
    return 0;
  }

//funzione per ritornare al menù una volta impostato il gioco
int inizia_gioco(){
  printf("\n!HAI IMPOSTATO CORRETTAMENTE IL GIOCO ORA PREMI INVIO PER RITORNARE AL MENU E GIOCARE!\n");
  getchar();
  return 0;
}

//creazione della stanza iniziale
stanza_inizio=(struct Stanza*) malloc(sizeof(struct Stanza));
//inizializzazione delle stanze
stanza_inizio->avanti=NULL;
stanza_inizio->sinistra=NULL;
stanza_inizio->destra=NULL;
stanza_inizio->stanza_precedente=NULL;
stanza_inizio->chiamata_emergenza=FALSE;

//creazione dell'array per assegnare in modo casuale le stanze
perc_room=rand()%100;
if(0<=perc_room&&perc_room<=25){
    stanza_inizio->tipo=3;
}
if(26<=perc_room&&perc_room<=40){
    stanza_inizio->tipo=2;
}
if(41<=perc_room&&perc_room<=70){
    stanza_inizio->tipo=1;
}
if(71<=perc_room&&perc_room<=100){
    stanza_inizio->tipo=0;
}
list_s=stanza_inizio;

for(int i=0;i<num_p;i++){
  player[i].pstanza=stanza_inizio;}

stampa_giocatori();
inizia_gioco();
return 0;
}

//inizio funziona gioca()
void gioca(){
srand((unsigned)time(&t));
int kill=FALSE;
int f=0;//variabile per determinare la conclusione del gioco
int* turni=malloc(num_p*sizeof(struct Giocatore));
do{
  //generazione casuale dei turni con i nomi presenti nell'array
for(int i=0;i<num_p;i++){
  turni[i]=rand()%num_p;
  for(int j=0;j<i;j++){
    if(turni[i]==turni[j]){
      i--;
    }
  }
}

for(int turno=0; turno<=num_p && f==0; turno++){
if (turno==num_p) {
  turno=0;
}
f=fine();
  //controllo dell condizione "assassinato"
kill=FALSE;
for (int i = 0; i <num_p; i++) {
    if (player[i].stato==2 && player[turni[turno]].pstanza->chiamata_emergenza==FALSE &&
    player[i].pstanza == player[turni[turno]].pstanza
    ) {
      kill=TRUE;
    }
  }

//inizio scorrimento turni
if (player[turni[turno]].stato==0 || player[turni[turno]].stato==1 ){

     printf("\t\n\nTurno di: %s\n", Nome_giocatore[player[turni[turno]].nome]);
     printf("Ti trovi in una stanza di tipo: %s\n", Tipo_stanza[player[turni[turno]].pstanza->tipo]);
     for(int i=0;i<num_p;i++){
       if(player[i].pstanza==player[turni[turno]].pstanza && player[i].nome!=player[turni[turno]].nome && (player[i].stato!=2 || player[i].stato!=3)){
        playerstanza++;
      }
    }
  if(playerstanza==0){
    printf("\nZero giocatori presenti nella stanza!\n");
    }
  else{
    printf("\n\t|GIOCATORI IN STANZA|: \n\n");
    for(int i=0;i<num_p;i++){
      if(player[i].pstanza==player[turni[turno]].pstanza && player[i].nome!=player[turni[turno]].nome && (player[i].stato!=2 || player[i].stato!=3)){
        printf("%s\n", Nome_giocatore[player[i].nome]);
      }
    }
  }
//Astronauti
if (player[turni[turno]].stato==0){
  printf("\n(1)AVANZA" );

  if (kill==TRUE) {
  printf(" (2)CHIAMATA EMERGENZA\n");
  }

  if (player[turni[turno]].pstanza->tipo==1||player[turni[turno]].pstanza->tipo==2) {
  printf(" (3)ESEGUI QUEST\n" );
  }

  printf("\ninserisci l'azione che vuoi fare:\n" );
  scanf("%d", &sc);
  while((ch= getchar() !='\n' && ch !=EOF));
  switch (sc) {
    case 1:
    avanza(turni, turno);
    break;
    case 2:
    chiamata_emergenza(turni, turno);
    break;
    case 3:
    esegui_quest(turni, turno);
    break;
    default:
    printf("\ncomando  sbagliato" );
    break;
  }
}
//Impostori
  if (player[turni[turno]].stato==1){
    printf("\n(1)AVANZA" );

    if (kill==TRUE) {
    printf(" (2)CHIAMATA EMERGENZA\n");
    }

    if(player[turni[turno]].pstanza->tipo==1||player[turni[turno]].pstanza->tipo==2){
      printf(" (3)SABOTA QUEST\n");
    }


    printf(" (4)UCCIDI ASTRONAUTA\n");


    if (player[turni[turno]].pstanza->tipo==3) {
    printf(" (5)USA BOTOLA\n" );
    }

    printf("\ninserisci l'azione che vuoi fare:\n" );
    scanf("%d", &sc);
    while((ch= getchar() !='\n' && ch !=EOF));
    switch (sc) {
      case 1:
      avanza(turni, turno);
      break;
      case 2:
      chiamata_emergenza(turni, turno);
      break;
      case 3:
      sabotaggio(turni, turno);
      break;
      case 4:
      uccidi_astronauta(turni, turno);
      break;
      case 5:
      usa_botola(turni, turno);
      break;
      default:
      printf("\ncomando  sbagliato" );
      break;
        }
      }
    }
}
}while(f==1);
termina_gioco();
}
