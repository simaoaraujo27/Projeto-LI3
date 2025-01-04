#ifndef _ERROS_H_
#define _ERROS_H_

typedef struct ficheiroErrosCSV FicheiroErrosCSV;

FicheiroErrosCSV *initFicheiroErrosCSV();

void WriteErrorsFile(FicheiroErrosCSV *ficheiroErrosCSV, char *typeFile,
                     char *line);

void destroyFicheiroErrosCSV(FicheiroErrosCSV *ficheiroErrosCSV);

#endif