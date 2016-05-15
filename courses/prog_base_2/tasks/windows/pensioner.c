#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pensioner.h"

#define NUM 300

char* pensioner_print(pensioner_t * pe) {
    char *s = malloc(NUM * sizeof(char));
    sprintf(s, "Name: %s\nSurname: %s\nBirthDate: %s\nPension: %f\nExperience: %i\n\n",
        pe->name, pe->surname, pe->birthDate, pe->pension, pe->experience);
    return s;
}

pensioner_t pensioner_fill(char *name, char *surname, char *birthDate, float pension, int experience) {
    pensioner_t pensioner;
    strcpy (pensioner.name, name);
    strcpy (pensioner.surname, surname);
    strcpy (pensioner.birthDate, birthDate);
    pensioner.pension = pension;
    pensioner.experience = experience;
    return pensioner;
}
