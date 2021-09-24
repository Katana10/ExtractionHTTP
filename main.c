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
  char html[TAILLE_MAX]= "";
  char * p;
  char* url="";
  char* fichier_txt="";
  char* nom_balise = "";
  
  //ouverture et extraction du HTML
  CURL *session = curl_easy_init();
  curl_easy_setopt(session, CURLOPT_URL, url);
  FILE * fp = fopen("./index_ccm.html", "w");
  curl_easy_setopt(session,  CURLOPT_WRITEDATA, fp);
  curl_easy_setopt(session,  CURLOPT_WRITEFUNCTION, fwrite);
  curl_easy_perform(session);
  fclose(fp);
  curl_easy_cleanup(session);


  //extraction des données
  fp = fopen("./index_ccm.html", "r+");
  //écriture lorsqu'il n'y a rien dans le fichier (ou si vous voulez supprimer les valeurs déja entrées)
  FILE *fichier = fopen("./fichier_txt", "w");
  //écriture lorsqu'il y a déja quelque chose dans le fichier et qu'on veux écrire à la suite (pas de suppression)
  //FILE *fichier = fopen("./fichier_txt", "a+");
 
  while(fgets(html, TAILLE_MAX,fp)!=NULL){


    if ((p = strstr(html, nom_balise)) != NULL){

      const char * separators = "<"">";

      // On cherche à récupérer, un à un, tous les mots (token) de la phrase
      // et on commence par le premier.

      char * strToken = strtok ( p, separators );
      while ( strToken != NULL ) {



        if ((strstr(strToken,"/span") == NULL) && (strstr(strToken,nom_balise) == NULL)) {
          printf ( "%s", strToken );
          fprintf(fichier, "%s", strToken);
        }

        // On demande le token suivant.
        strToken = strtok ( NULL, separators );
      }

      //printf("%s\n", html);
      //*p = '\0';
      compteur++;
    }
  }
  printf("%d\n", compteur);
  fclose(fichier);
  fclose(fp);
  return 0;
}
