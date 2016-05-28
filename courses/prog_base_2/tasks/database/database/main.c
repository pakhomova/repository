#include <stdio.h>
#include <stdlib.h>
#include "db_manager.h"
#include "pensioner.h"

#define PENUMBER 10

int main(void) {
    const char *dbFile = "database.db";

    db_t *db = db_new(dbFile);

    pensioner_t pensioner1 = {0, "Zhenya", "Pahomova", "19.03.1998", 9999.99, 100};
    pensioner_t pensioner2 = {0, "Roman", "Kushnirenko", "11.06.1996", 9999999.99, 10};
    pensioner_t pensioner3 = {0,"Ivan", "Ivanov", "15.05.1998", 1234.99, 19};
    pensioner_t pensioner4 = {0, "Petro", "Petrov", "21.01.1901", 777, 77};
    pensioner_t pensioner5 = {0, "Irina", "Timofeeva", "01.12.1990", 9991, 12};

    int id1, id2, id3, id4, id5;

    id1 = db_insertPensioner (db, &pensioner1);
    id2 = db_insertPensioner (db, &pensioner2);
    id3 = db_insertPensioner (db, &pensioner3);
    id4 = db_insertPensioner (db, &pensioner4);
    id5 = db_insertPensioner (db, &pensioner5);

    pensioner_t *pensioners = malloc (10 * sizeof(pensioner_t));

    int count = db_getPensioners(db, pensioners);
    //int count = db_getPensioners(db, pensioners);

    puts("TEST!\n");

    pensioner_printList(pensioners, count);

    free (pensioners);
    db_free(db);
    return 0;
}
