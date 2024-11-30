#ifndef SEMAPHORE_H
#define SEMAPHORE_H

void erreurFin(const char* msg);
void initSem(short unsigned nbSem, char* nomFich, int* pvinit);
void libereSem();
void P(short unsigned numSem);
void V(short unsigned numSem);

#endif
