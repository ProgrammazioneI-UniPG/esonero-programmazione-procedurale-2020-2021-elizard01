#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_len  129
#define plain_t_len 140

char plain_text [plain_t_len];
char key_text [max_len];
char encrypted_text [max_len];
char string_choice [max_len];

int user_choice;
int c; //usato con getchar () per svuotare il buffer

int main (){

  time_t t;
  srand ((unsigned) time(& t));

  printf ("\n\n################### Algoritmo di cifratura RC4 ###################\n\n");

  printf ("\nDigitare il testo da cifrare. ATTENZIONE: numero massimo di caratteri consentito (compresi gli spazi): %d\n\n", max_len - 1);
  fgets (plain_text, plain_t_len, stdin);
  printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");


  while (strlen (plain_text)>=max_len){
    printf ("\nERRORE!\n Il testo inserito supera il numero massimo di caratteri consentito (%d).\n\n", max_len - 1);
    while ((c = getchar ()) != '\n')
      c = 0;
    fgets (plain_text, plain_t_len, stdin);

    printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
  }

  printf ("\n\nCome si vuole procedere? Digitare:\n\n1 -> per digitare da tastiera la chiave di cifratura\n\n2 -> per generare casualmente una chiave di cifratura\n\n");
    fgets (string_choice, max_len, stdin);
    sscanf (string_choice, "%d", & user_choice);
  printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");

  while (user_choice != 1 && user_choice != 2){
    printf ("\n\nValore inserito non valido\n\n\nScegliere tra:\n\n1 -> per digitare da tastiera la chiave di cifratura\n\n2 -> per generare casualmente una chiave di cifratura\n\n");
      fgets (string_choice, max_len, stdin);
      sscanf (string_choice, "%d", & user_choice);
    printf ("\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");
  }

  switch (user_choice){

    case 1:{
        printf ("\n\nDigitare la chiave di cifratura che si desidera utilizzare.\n\nRICORDA: il numero di caratteri della chiave deve essere almeno uguale a quello del testo da criptare\nNOTA: le lettere accentate hanno bisogno di due caratteri per essere criptate\n\n");
        fgets (key_text, max_len, stdin);
        printf ("\n\n-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-");

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
