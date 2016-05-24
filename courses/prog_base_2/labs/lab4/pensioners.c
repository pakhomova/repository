#include "pensioners.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//pensioner

pensioner_t *pensioner_create (int id, char *name, char *surname, struct tm birthDate, float pension, int experience) { //конструктор пенсионера
    pensioner_t *p = malloc(sizeof(struct pensioner_s));
    p->id = id;
    strcpy (p->name, name);
    strcpy (p->surname, surname);
    p->birthDate = birthDate;
    p->pension = pension;
    p->experience = experience;
    return p;
}

pensioner_t *pensioner_copy (pensioner_t *pensioner) { //конструктор копии
    pensioner_t *p = pensioner_create(pensioner->id, pensioner->name, pensioner->surname, pensioner->birthDate, pensioner->pension, pensioner->experience);
    return p;
}

void pensioner_delete (pensioner_t *pensioner) {
    free (pensioner);
}

static int findPensioner (pensioner_t *pensionerArray, int size, int id) { //поиск индеска пенсионера по айди
    int i;
    for (i = 0; i < size; i++)
        if (pensionerArray[i].id == id) return i;
    return -1;
}

//pensioners

pensioners_t *pensioners_create () {  //конструктор массива пенсионеров
    pensioners_t *pensioners = malloc(sizeof(struct pensioners_s));
    pensioners->number = 0;
    pensioners->pensionerArray = malloc(0);
    return pensioners;
}

int pensioners_count (pensioners_t *pensioners) { //количество пенсионеров
    return pensioners->number;
}

void pensioners_insert (pensioners_t *pensioners, pensioner_t *pensioner) {
    (pensioners->number)++;
    pensioner_t *p = malloc(pensioners->number * sizeof(pensioner_t));
    int i;
    for (i = 0; i < pensioners->number - 1; i++)
        p[i] = *pensioner_copy(&pensioners->pensionerArray[i]);
    p[pensioners->number - 1] = *pensioner_copy (pensioner);
    p[pensioners->number - 1].id = pensioners->number == 1 ? 1 : p[pensioners->number - 2].id + 1;
    free (pensioners->pensionerArray);
    pensioners->pensionerArray = p;
}

pensioner_t *pensioners_get (pensioners_t *pensioners, int id) { //получаем указатель на пенсионера с данным айди
    int ind = findPensioner(pensioners->pensionerArray, pensioners->number, id);
    if (ind == -1) return NULL;
    return pensioner_copy(&pensioners->pensionerArray[ind]);
}

void pensioners_update (pensioners_t *pensioners, int id, pensioner_t *pensioner) { //заменяем старого пенсионера на нового
    int ind = findPensioner(pensioners->pensionerArray, pensioners->number, id);
    if (ind != -1) {
        pensioner->id = id;
        pensioners->pensionerArray[ind] = *pensioner_copy(pensioner);
    }
}

int pensioners_remove (pensioners_t *pensioners, int id) {
    int ind = findPensioner(pensioners->pensionerArray, pensioners->number, id);
    if (ind == -1) return 0;
    (pensioners->number)--;
    pensioner_t *p = malloc(pensioners->number * sizeof(pensioner_t));
    int i;
    for (i = 0; i < ind; i++)
        p[i] = *pensioner_copy(&pensioners->pensionerArray[i]);
    for (i = ind + 1; i < pensioners->number + 1; i++)
        p[i - 1] = *pensioner_copy(&pensioners->pensionerArray[i]);
    free (pensioners->pensionerArray);
    pensioners->pensionerArray = p;
    return 1;
}

void pensioners_delete (pensioners_t *pensioners) {
    free (pensioners->pensionerArray);
    free (pensioners);
}
