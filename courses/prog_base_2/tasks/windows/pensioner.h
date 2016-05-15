#ifndef PENSIONER_H_INCLUDED
#define PENSIONER_H_INCLUDED

#define LEN 30

typedef struct pensioner_s {
    char name[LEN];
    char surname[LEN];
    char birthDate[LEN];
    float pension;
    int experience;
} pensioner_t;

char* pensioner_print (pensioner_t * pe);
pensioner_t pensioner_fill(char *name, char *surname, char *birthDate, float pension, int experience);

#endif

