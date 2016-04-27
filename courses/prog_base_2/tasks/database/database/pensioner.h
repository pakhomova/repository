#ifndef PENSIONER_H_INCLUDED
#define PENSIONER_H_INCLUDED

#define LEN 256

typedef struct pensioner_s {
    int id;
    char name[LEN];
    char surname[LEN];
    char birthDate[LEN];
    float pension;
    int experience;
} pensioner_t;

void pensioner_print(pensioner_t * pe);
void pensioner_printList(pensioner_t * arr, int len);

#endif
