#define _GNU_SOURCE
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1000

// Pour que le programme focntionne il faut le compiler avec un -lcurl
int main(int argc, char **argv){
  // Définition des variaables
  int compteur=0;
  char recette[TAILLE_MAX]= "";
  char * p;
  char *comp1;
  char *comp2;



  CURL *session = curl_easy_init();
  curl_easy_setopt(session, CURLOPT_URL, "https://www.cuisine-etudiant.fr/recettes/page-2");
  FILE * fp = fopen("./index_ccm.html", "w");
  curl_easy_setopt(session,  CURLOPT_WRITEDATA, fp);
  curl_easy_setopt(session,  CURLOPT_WRITEFUNCTION, fwrite);
  curl_easy_perform(session);
  fclose(fp);
  curl_easy_cleanup(session);


  //extraction des données
  fp = fopen("./index_ccm.html", "r+");
  FILE *fichier = fopen("./recette.txt", "w");
  //FILE *fichier = fopen("./recette.txt", "a+");
  char* test = "recipes-list-title";
  while(fgets(recette, TAILLE_MAX,fp)!=NULL){


    if ((p = strstr(recette, test)) != NULL){

      const char * separators = "<"">";

      // On cherche à récupérer, un à un, tous les mots (token) de la phrase
      // et on commence par le premier.

      char * strToken = strtok ( p, separators );
      while ( strToken != NULL ) {



        if ((strstr(strToken,"/span") == NULL) && (strstr(strToken,test) == NULL)) {
          // printf("caca\n" );
          printf ( "%s", strToken );
          fprintf(fichier, "%s", strToken);
        }

        // On demande le token suivant.
        strToken = strtok ( NULL, separators );
      }

      //printf("%s\n", recette);
      //*p = '\0';
      compteur++;
    }
  }
  printf("%d\n", compteur);
  fclose(fichier);
  fclose(fp);
  return 0;
}
