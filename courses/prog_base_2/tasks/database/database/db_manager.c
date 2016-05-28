#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sqlite3.h"

#include "db_manager.h"
#include "pensioner.h"

struct db_s {
    sqlite3 *db;
};

db_t *db_new(const char * dbFile) {
    db_t *self = malloc(sizeof(struct db_s));
    int rc = sqlite3_open(dbFile, &self->db);
    if (SQLITE_ERROR == rc) {
        printf("can't open database\n");
        exit(1);
    }
    return self;
}

void db_free(db_t *self) {
    sqlite3_close(self->db);
    free(self);
}

int db_insertPensioner(db_t *self, pensioner_t *pensioner) {
    sqlite3_stmt *stmt = NULL;
    const char *sqlInsertCommand = "INSERT INTO Pensioner ('Name', 'Surname', 'BirthDate', 'Pension', 'Experience') VALUES (?,?,?,?,?);";

    sqlite3_prepare_v2(self->db, sqlInsertCommand, strlen(sqlInsertCommand) + 1, &stmt, NULL);

    sqlite3_bind_text (stmt, 1, pensioner->name, -1, SQLITE_STATIC);
    sqlite3_bind_text (stmt, 2, pensioner->surname, -1, SQLITE_STATIC);
    sqlite3_bind_text (stmt, 3, pensioner->birthDate, -1, SQLITE_STATIC);
    sqlite3_bind_double (stmt, 4, pensioner->pension);
    sqlite3_bind_int (stmt, 5, pensioner->experience);

    sqlite3_step(stmt);

    pensioner->id = (int)sqlite3_last_insert_rowid(self->db);
    sqlite3_reset(stmt);
    return pensioner->id;
}

pensioner_t *db_getPensionerById(db_t *self, int id) {
    pensioner_t *pensioner = malloc(sizeof(struct pensioner_s));
    sqlite3_stmt *stmt = NULL;
    const char *sqlGetCommand = "SELECT * FROM Pensioner WHERE Id=?;";

    sqlite3_prepare_v2(self->db, sqlGetCommand, strlen(sqlGetCommand) + 1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        pensioner->id = 0;
        strcpy (pensioner->name, "NoUserName");
        strcpy (pensioner->surname, "NoUserSurname");
        pensioner->experience = 0;
        pensioner->pension = 0.0;
        strcpy (pensioner->birthDate, "NoUserBirthdate");
        return pensioner;
    }
    pensioner->id = id;
    strcpy (pensioner->name, (char *)sqlite3_column_text(stmt, 1));
    strcpy (pensioner->surname, (char *)sqlite3_column_text(stmt, 2));
    strcpy (pensioner->birthDate, (char *)sqlite3_column_text(stmt, 3));
    pensioner->pension = sqlite3_column_double(stmt, 4);
    pensioner->experience = sqlite3_column_int(stmt, 5);

    sqlite3_reset (stmt);

    return pensioner;
}

int db_updatePensioner(db_t *self, pensioner_t *pensioner) {
    sqlite3_stmt *stmt = NULL;
    const char *sqlUpdateCommand = "UPDATE Pensioner SET "
                                   "Name=?,"
                                   "Surname=?,"
                                   "BirthDate=?,"
                                   "Pension=?,"
                                   "Experience=? "
                                   "WHERE Id=?;";

    sqlite3_prepare_v2(self->db, sqlUpdateCommand, strlen(sqlUpdateCommand) + 1, &stmt, NULL);

    sqlite3_bind_text (stmt, 1, pensioner->name, -1, SQLITE_STATIC);
    sqlite3_bind_text (stmt, 2, pensioner->surname, -1, SQLITE_STATIC);
    sqlite3_bind_text (stmt, 3, pensioner->birthDate, -1, SQLITE_STATIC);
    sqlite3_bind_double (stmt, 4, pensioner->pension);
    sqlite3_bind_int (stmt, 5, pensioner->experience);
    sqlite3_bind_int (stmt, 6, pensioner->id);

    sqlite3_step (stmt);
    sqlite3_reset (stmt);

    return 0;
}

int db_deletePensionerById (db_t *self, int id) {
    sqlite3_stmt *stmt = NULL;
    const char *sqlDeleteCommand = "DELETE FROM Pensioner WHERE Id=?";

    sqlite3_prepare_v2(self->db, sqlDeleteCommand, strlen(sqlDeleteCommand) + 1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, id);

    sqlite3_step(stmt);
    sqlite3_reset(stmt);

    return 0;
}

static void _fillPensioner (sqlite3_stmt *stmt, pensioner_t *pe) {
    int id = sqlite3_column_int (stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    const unsigned char *surname = sqlite3_column_text(stmt, 2);
    const unsigned char *birthDate = sqlite3_column_text(stmt, 3);
    double pension = sqlite3_column_double(stmt, 4);
    int experience = sqlite3_column_int(stmt, 5);

    pe->id = id;
    strcpy (pe->name, (const char *)name);
    strcpy (pe->surname, (const char *)surname);
    strcpy (pe->birthDate, (const char *)birthDate);
    pe->pension = pension;
    pe->experience = experience;
}

int db_getPensionersSize(db_t *self) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Pensioner;";
    sqlite3_prepare_v2 (self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    int sizeSum = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ERROR) {
            printf("Can't select Pensioners\n");
            exit(1);
        } else if (rc == SQLITE_DONE) {
            break;
        } else {
            //4     int id = sqlite3_column_int (stmt, 0);
            int name_len = strlen(sqlite3_column_text(stmt, 1));
            int surname_len = strlen(sqlite3_column_text(stmt, 2));
            int birthday_len = strlen(sqlite3_column_text(stmt, 3));
            //16    double pension = sqlite3_column_double(stmt, 4);
            //4     int experience = sqlite3_column_int(stmt, 5);

            sizeSum += 4 + 4 + 16 + name_len + surname_len + birthday_len;
        }
    }
    sqlite3_finalize(stmt);
    return sizeSum;
}

int db_getPensioners(db_t *self, pensioner_t *arr) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Pensioner;";
    sqlite3_prepare_v2 (self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ERROR) {
            printf("Can't select Pensioners\n");
            exit(1);
        } else if (rc == SQLITE_DONE) {
            break;
        } else {
            _fillPensioner(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}

int db_getPensionersTask(db_t *self, int K, int P, pensioner_t *arr) {
    sqlite3_stmt * stmt = NULL;
    const char * sqlQuery = "SELECT * FROM Pensioner WHERE Experience > ? AND Pension < ?;";
    sqlite3_prepare_v2 (self->db, sqlQuery, strlen(sqlQuery), &stmt, 0);
    sqlite3_bind_int (stmt, 1, K);
    sqlite3_bind_int (stmt, 2, P);
    int count = 0;
    while (1) {
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ERROR) {
            printf("Can't select Pensioners\n");
            exit(1);
        } else if (rc == SQLITE_DONE) {
            break;
        } else {
            _fillPensioner(stmt, &arr[count]);
            count++;
        }
    }
    sqlite3_finalize(stmt);
    return count;
}
