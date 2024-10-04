/*
   Fichier base64.h
   Auteur Bernard Chardonneau
*/

/* prototypes des fonctions de la bibliothèque base64 */

#ifndef __BASE64_H__
#define __BASE64_H__

#ifdef __cplusplus
extern "C" {
#endif

void encode64 (char *orig, char *dest, int nbcar);
int  decode64 (char *buffer);

#ifdef __cplusplus
}
#endif

#endif
