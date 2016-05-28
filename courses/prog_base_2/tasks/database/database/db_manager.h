#ifndef DB_MANAGER_H_INCLUDED
#define DB_MANAGER_H_INCLUDED

#include "sqlite3.h"
#include "pensioner.h"

typedef struct db_s db_t;

db_t *db_new(const char *dbFile);
void db_free(db_t *self);

int db_insertPensioner(db_t *self, pensioner_t *pensioner);
pensioner_t *db_getPensionerById(db_t *self, int id);
int db_updatePensioner(db_t *self, pensioner_t *pensioner);
int db_deletePensionerById (db_t *self, int id);

int db_getPensionersTask(db_t *self, int K, int P, pensioner_t *arr);
int db_getPensionersSize(db_t *self);
int db_getPensioners(db_t *self, pensioner_t *arr);

#endif

