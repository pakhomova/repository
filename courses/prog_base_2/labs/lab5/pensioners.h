#ifndef PENSIONERS_H
#define PENSIONERS_H

#include <time.h>

#define NAME_LEN 50
#define SURNAME_LEN 50

typedef struct pensioner_s {
    int id;
    char name[NAME_LEN];
    char surname[SURNAME_LEN];
    struct tm birthdate;
    float pension;
    int experience;
} pensioner_t;

typedef struct pensioners_s pensioners_t;

pensioners_t *pensioners_create();
int pensioners_count (pensioners_t *pensioners);
void pensioners_insert(pensioners_t *pensioners, pensioner_t *pensioner);
pensioner_t *pensioners_get (pensioners_t *pensioners, int id);
void pensioners_get_all(pensioners_t *pensioners, pensioner_t **pensionerArray, int *count);
int pensioners_remove (pensioners_t *pensioners, int id);
void pensioners_filter(pensioners_t *pensioners, pensioner_t **pensionerArray, int *count, int k, int p);
void pensioners_delete(pensioners_t *pensioners);


#endif

