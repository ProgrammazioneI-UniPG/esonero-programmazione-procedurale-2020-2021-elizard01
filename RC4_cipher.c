#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_len  129

char plain_text [max_len];
char key_text [max_len];
char encrypted_text [max_len];
char string_choice [max_len];

int user_choice;
int c;

int main (){

  time_t t;

  srand ((unsigned) time(& t));
  //inizializzo la stringa per controllare il numero di caratteri inseriti
  for (int i = 0; i < max_len; i++)
    plain_text [i] = '\0';

  printf ("\n\n################### Algoritmo di cifratura RC4 ###################\n\n");

  printf ("\nDigitare il testo da cifrare. ATTENZIONE: numero massimo di caratteri consentito (compresi gli spazi e l'invio finale): %d\n\n", max_len - 1);
  fgets (plain_text, max_len, stdin);
  printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");

//controllo che la stringa non sia troppo lunga (cioè che il  carattere terminatore non si trovi oltre il 128) e che non sia composta solo da \n

  while((plain_text[max_len-2] != '\n' && plain_text [max_len-2] != '\0') || plain_text[0] == '\n'){

     if(plain_text[max_len-2] != '\n' && plain_text [max_len-2] != '\0'){

        printf ("\nERRORE: Il testo inserito supera la lunghezza massima consentita (%d).\nInserire messaggio più breve\n\n", max_len-1);
        while ((c=getchar ()) != '\n' && c != EOF);   //Bisogna sicuramente pulire, dato che il testo supera i 128 caratteri
        for (int i =0; i<= max_len; i++)  //Puliamo prima di riacquisire
          plain_text[i]='\0';
        fgets (plain_text, max_len, stdin);
        printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
     }

     else
        if(plain_text[0] == '\n'){
          printf("\nERRORE: Inserire almeno un carattere valido prima di premere invio \n\n");
          for (int i =0; i<= max_len; i++)  //Puliamo prima di riacquisire
            plain_text[i]='\0';
          fgets (plain_text, max_len, stdin);
          printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
     }
  }


  printf ("\n\nCome si vuole procedere? Digitare:\n\n1 -> per digitare da tastiera la chiave di cifratura\n\n2 -> per generare casualmente una chiave di cifratura\n\n");
    //inizializzo la stringa per la scelta. uso una stringa per evitare errori nel caso in cui l'utente inserisca dei char
    for (int i = 0; i<=max_len; i++)
      string_choice [i]='\0';
    fgets (string_choice, max_len, stdin);
    sscanf (string_choice, "%d", & user_choice);
  printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");

  while (user_choice != 1 && user_choice != 2){
      //controllo che la stringa inserita non sia troppo lunga, cioè che il  carattere terminatore non si trovi oltre il 128
      if (string_choice [max_len-2]!='\n'&& string_choice [max_len-2]!='\0'){

        printf ("\n\nValore inserito non valido\n\n\nScegliere tra:\n\n1 -> per digitare da tastiera la chiave di cifratura\n\n2 -> per generare casualmente una chiave di cifratura\n\n");
        while ((c=getchar())!='\n'&& c!=EOF) //svuoto il buffer stdin
        for (int i =0; i<=max_len; i++) //inizializzo di nuovo per il prossimo ipotetico controllo
          string_choice [i]='\0';
        fgets (string_choice, max_len, stdin);
        sscanf (string_choice, "%d", & user_choice);
        printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
      }
    //se le dimensioni sono giuste, controllo di avere un valore valido
    else
         {
            printf ("\n\nValore inserito non valido\n\n\nScegliere tra:\n\n1 -> per digitare da tastiera la chiave di cifratura\n\n2 -> per generare casualmente una chiave di cifratura\n\n");
            fgets (string_choice, max_len, stdin);
            sscanf (string_choice, "%d", & user_choice);
            printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
          }
  }

  switch (user_choice){

    case 1:{
        printf ("\n\nDigitare la chiave di cifratura che si desidera utilizzare.\n\nRICORDA: il numero di caratteri della chiave deve essere almeno uguale a quello del testo da criptare\nNOTA: le lettere accentate hanno bisogno di due caratteri per essere criptate\n\n");
        for (int i =0; i<=max_len; i++)//inizializzione per controllo dimensioni
          key_text[i]='\0';
        fgets (key_text, max_len, stdin);
        printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");

        //controllo che la stringa inserita non sia troppo lunga, cioè che il  carattere terminatore non si trovi oltre il 128
        while (key_text[max_len-2]!='\n' && key_text[max_len-2]!='\0'){

          printf ("\n\nATTENZIONE: La chiave digitata supera il numero massimo di caratteri consentiti (%d).\nInserire chiave più breve\n\n", max_len-1);
          while ((c=getchar())!='\n' && c!=EOF) //libero il buffer stdin
          for (int i =0; i<=max_len;i++) //inizializzo prima di riacquisire
            key_text[i]='\0';
          fgets (key_text, max_len, stdin);
          printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
        }
        //controllo che non la chiave non sia troppo corta
        while (strlen (key_text)< strlen (plain_text)){
            printf("\n\nLa chiave digitata è troppo corta. Inserire una chiave che abbia ALMENO %ld caratteri\n\n", strlen (plain_text)-1);
            fgets (key_text, max_len, stdin);
            printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
            }
        break;
      }

    case 2:
        for (int i=0; i < strlen (plain_text)-1; i++)
          key_text [i]= (rand () % 96)+31;
      break;

    default:
        printf ("\n\nERROR\n\n");
      break;
    }

  printf ("\n\nLa chiave di cifratura è:\n\n");
  fputs (key_text, stdout);
  printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
  printf ("\n\n\n");

//CIFRATURA
  for (int i=0; i<strlen (plain_text)-1; i++)
    encrypted_text [i] = (plain_text [i] ^ key_text [i])+31;

  printf ("Il testo cifrato è:\n\n");
  fputs (encrypted_text, stdout);
  printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
  printf ("\n\n\n");

//DECIFRATURA
  for (int i=0; i<strlen (encrypted_text)-1; i++)
    plain_text [i] = (encrypted_text [i]-31) ^ key_text [i];

  printf ("Il testo decifrato è:\n\n");
  fputs (plain_text, stdout);
  printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
  printf ("\n\n\n");

  return 0;
}
