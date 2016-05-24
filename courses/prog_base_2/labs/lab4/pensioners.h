#ifndef PENSIONERS_H
#define PENSIONERS_H

#include <time.h>

#define NAME_LEN 50
#define SURNAME_LEN 50

typedef struct pensioner_s {
    int id;
    char name[NAME_LEN];
    char surname[SURNAME_LEN];
    struct tm birthDate;
    float pension;
    int experience;
} pensioner_t;

typedef struct pensioners_s {
    int number;
    pensioner_t *pensionerArray;
} pensioners_t;

//pensioner

pensioner_t *pensioner_create (int id, char *name, char *surname, struct tm birthDate, float pension, int experience);
pensioner_t *pensioner_copy (pensioner_t *pensioner);
void pensioner_delete (pensioner_t *pensioner);

//pensioners

pensioners_t *pensioners_create ();
int pensioners_count (pensioners_t *pensioners);
void pensioners_insert (pensioners_t *pensioners, pensioner_t *pensioner);
pensioner_t *pensioners_get (pensioners_t *pensioners, int id);
void pensioners_update (pensioners_t *pensioners, int id, pensioner_t *pensioner);
int pensioners_remove (pensioners_t *pensioners, int id);
void pensioners_delete (pensioners_t *pensioners);

#endif
