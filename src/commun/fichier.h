#ifndef FICHIER_H
#define FICHIER_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int creerFDFichierEnLecture(const char* chemin);
ssize_t lireUnFichier(const int fdFichier, void* tampon, const size_t nombreDOctetesALire);
int fermerFichier(const int fdFichier);

#endif
