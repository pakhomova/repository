#ifndef PENSIONER_H
#define PENSIONER_H

#include <time.h>

#define LEN 50
#define PENCOUNT 3

typedef struct pensioner_s {
    char name[LEN];
    char surname[LEN];
    struct tm birthDate;
    float pension;
    int experience;
} pensioner_t;

pensioner_t *pensioner_new (void);
void pensioner_delete (pensioner_t *pensioner);

void xmlParse (pensioner_t *pensionerSet[], const char *XMLFileName);
void printPensionerInfo (pensioner_t *pensioner);

#endif
