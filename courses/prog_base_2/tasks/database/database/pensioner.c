#include <stdlib.h>
#include <stdio.h>

#include "pensioner.h"

void pensioner_print(pensioner_t * pe) {
    printf("Name: %s\nSurname: %s\nBirthDate: %s\nPension: %f\nExperience: %i\n\n",
        pe->name, pe->surname, pe->birthDate, pe->pension, pe->experience);
}

void pensioner_printList(pensioner_t * arr, int len) {
    int i;
    for (i = 0; i < len; i++) {
        pensioner_print(&arr[i]);
    }
}
