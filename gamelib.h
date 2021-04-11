#include <stdio.h>
#include <stdlib.h>
#ifndef _GAMELIBH_
#define _GAMELIBH_
int imposta_gioco();
void gioca();
void termina_gioco();

enum Stato_giocatore{astronauta,impostore,assassinato,defenestrato};
enum Nome_giocatore{rosso,giallo,blu,verde,viola,nero,marrone,arancione,rosa,bianco};
enum Tipo_stanza{vuota, quest_semplice, quest_complicata, botola};

typedef enum chiamata_emergenza {FALSE, TRUE} boolean;

struct Stanza{
  struct Stanza* avanti;
  struct Stanza* sinistra;
  struct Stanza* destra;
  struct Stanza* stanza_precedente;
  struct Stanza* next_room;
  enum Tipo_stanza tipo;
  enum chiamata_emergenza  chiamata_emergenza;
};

 struct Giocatore{
  struct Stanza* pstanza;
  enum Stato_giocatore stato;
  enum Nome_giocatore nome;
};
#endif
