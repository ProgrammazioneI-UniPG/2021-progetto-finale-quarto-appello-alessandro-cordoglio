#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gamelib.h"

// Questo file continene solo la definizione della funzione main
// con il menu principale 1-2-3

int main( ) {
    int scelta;
    bool flag_impostagioco=false;

    do {
      printf("             ______________________________________________________________________ \n" );
      printf("            |                              Benvenuto in                            |\n" );
      printf("            |                       |--------TRANNOI--------|                      |\n" );
      printf("            | Seleziona un'opzione per continuare                                  |\n" );
      printf("            | 1) Imposta gioco                                                     |\n" );
      printf("            | 2) Gioca                                                             |\n" );
      printf("            | 3) Termina gioco                                                     |\n" );
      printf("            |______________________________________________________________________|\n" );

      scanf("%d", &scelta );
      while(getchar()!='\n');
      switch (scelta)
	  {
    		case 1:
    		imposta_gioco();
        flag_impostagioco=true;
    		break;

    		case 2:
        if(flag_impostagioco){
          gioca();
          flag_impostagioco= false;
        }
        else
        printf("prima imposta il gioco\n" );
    		break;

    		case 3:
    		termina_gioco();
    		break;

        default:
        printf("errore di immissione\n");
    }

} while(scelta!=1||scelta!=3);
  return 0;

}
