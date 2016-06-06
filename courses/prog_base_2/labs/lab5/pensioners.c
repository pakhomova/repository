#include "pensioners.h"

#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <stdio.h>

#define SQLLEN 1024

struct pensioners_s {
    sqlite3 *db;
};

pensioners_t *pensioners_create() {//возвращает структуру пенсионеров с подвязаной бд
    char sql[SQLLEN];
    sqlite3_stmt *stmt;//создаеи стейтмент

    pensioners_t *pensioners = malloc(sizeof(pensioners_t));//создаем память для пенсионеров
    sqlite3_open("pensioners.db", &pensioners->db);//подвязываем структуру к базе данных

    strcpy (sql, "SELECT name FROM sqlite_master WHERE type='table' AND name='pensioners';");//ищем таблицу
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);//пождязываем стейтмент к скл-запросу

    int status = sqlite3_step(stmt);//стейтмент начинает обрабатываться
    if (status != SQLITE_ROW) {//если таблицы нет
        sqlite3_finalize(stmt);
        //создаем таблицу
        strcpy (sql, "CREATE TABLE `pensioners` (" \
                "`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE," \
                "`name` TEXT NOT NULL," \
                "`surname` TEXT NOT NULL," \
                "`birthdate` TEXT NOT NULL," \
                "`pension` REAL NOT NULL," \
                "`experience` INTEGER NOT NULL DEFAULT 0);");
        sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);

    return pensioners;
}

int pensioners_count (pensioners_t *pensioners) {//считаем пенсионеров
    char sql[SQLLEN];
    sqlite3_stmt *stmt;

    strcpy(sql, "SELECT COUNT(*) FROM pensioners;");//считаем колл-во строк в таблице
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
    sqlite3_step(stmt);
    int count = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);
    return count;
}

void pensioners_insert(pensioners_t *pensioners, pensioner_t *pensioner) {
    char sql[SQLLEN];
    sqlite3_stmt *stmt;
    //создаем строку в таблице
    strcpy (sql, "INSERT INTO " \
            "pensioners (name,surname,birthdate,pension,experience)" \
            "VALUES (?,?,?,?,?);");
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, pensioner->name, -1, NULL);//подвязываем данные к запросу(строке)
    sqlite3_bind_text(stmt, 2, pensioner->surname, -1, NULL);

    char buffer[64];
    sprintf(buffer, "%i-%i-%i", pensioner->birthdate.tm_year + 1900, pensioner->birthdate.tm_mon + 1, pensioner->birthdate.tm_mday);

    sqlite3_bind_text(stmt, 3, buffer, -1, NULL);

    sqlite3_bind_double(stmt, 4, pensioner->pension);
    sqlite3_bind_int(stmt, 5, pensioner->experience);

    sqlite3_step(stmt);//обрабатывается запрос, создается строка
    sqlite3_finalize(stmt);
}

pensioner_t *pensionerPersistantPtr = NULL;

pensioner_t *pensioners_get (pensioners_t *pensioners, int id) {
    if (pensionerPersistantPtr) {//если указатель на пенсионера не пустой
        free(pensionerPersistantPtr);
        pensionerPersistantPtr = NULL;
    }

    char sql[SQLLEN];
    sqlite3_stmt *stmt;

    strcpy(sql, "SELECT * FROM pensioners WHERE id=?;");//выбрать все строки с соответствующим айди(либо 1, либо 0)
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    int status = sqlite3_step(stmt);

    if (status == SQLITE_ROW) {
        pensionerPersistantPtr = malloc(sizeof(pensioner_t));

        pensionerPersistantPtr->id = sqlite3_column_int(stmt, 0);//вытаскиваем данные из колонок
        strcpy(pensionerPersistantPtr->name, (char *)sqlite3_column_text(stmt, 1));
        strcpy(pensionerPersistantPtr->surname, (char *)sqlite3_column_text(stmt, 2));

        sscanf((char *)sqlite3_column_text(stmt, 3), "%i-%i-%i", &pensionerPersistantPtr->birthdate.tm_year, &pensionerPersistantPtr->birthdate.tm_mon, &pensionerPersistantPtr->birthdate.tm_mday);
        pensionerPersistantPtr->birthdate.tm_year -= 1900;
        pensionerPersistantPtr->birthdate.tm_mon -= 1;

        pensionerPersistantPtr->pension = sqlite3_column_double(stmt, 4);
        pensionerPersistantPtr->experience = sqlite3_column_int(stmt, 5);
    }

    sqlite3_finalize(stmt);

    return pensionerPersistantPtr;
}

void pensioners_get_all(pensioners_t *pensioners, pensioner_t **pensionerArray, int *count) {//возвращает массив пенсионеров
    if (pensionerPersistantPtr)//если массив не пустой
        free(pensionerPersistantPtr);
    pensionerPersistantPtr = malloc(0);

    char sql[SQLLEN];
    sqlite3_stmt *stmt;

    strcpy(sql, "SELECT * FROM pensioners;");
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
    int status;
    *count = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {

            pensionerPersistantPtr = realloc(pensionerPersistantPtr, (*count + 1) * sizeof(pensioner_t));//расширяем массив пенсионеров

            pensionerPersistantPtr[*count].id = sqlite3_column_int(stmt, 0);
            strcpy(pensionerPersistantPtr[*count].name, (char *)sqlite3_column_text(stmt, 1));
            strcpy(pensionerPersistantPtr[*count].surname, (char *)sqlite3_column_text(stmt, 2));

            sscanf((char *)sqlite3_column_text(stmt, 3), "%i-%i-%i", &pensionerPersistantPtr[*count].birthdate.tm_year, &pensionerPersistantPtr[*count].birthdate.tm_mon, &pensionerPersistantPtr[*count].birthdate.tm_mday);
            pensionerPersistantPtr[*count].birthdate.tm_year -= 1900;
            pensionerPersistantPtr[*count].birthdate.tm_mon -= 1;

            pensionerPersistantPtr[*count].pension = sqlite3_column_double(stmt, 4);
            pensionerPersistantPtr[*count].experience = sqlite3_column_int(stmt, 5);

            ++(*count);
        } else
            break;
    }

    *pensionerArray = pensionerPersistantPtr;

    sqlite3_finalize(stmt);
}

int pensioners_remove (pensioners_t *pensioners, int id) {
    char sql[SQLLEN];
    sqlite3_stmt *stmt;

    strcpy(sql, "DELETE FROM pensioners " \
            "WHERE id=?;");
    sqlite3_prepare_v2(pensioners->db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return 1;
}

void pensioners_filter(pensioners_t *pensioners, pensioner_t **pensionerArray, int *count, int k, int p) {//возвращает массив пенсионеров, который прошел фильтр
    if (pensionerPersistantPtr)
        free(pensionerPersistantPtr);
    pensionerPersistantPtr = malloc(0);

    char sql[SQLLEN];
    sqlite3_stmt *stmt;

    strcpy(sql, "SELECT * FROM pensioners WHERE experience > %u AND pension > %u;");//делаем фильтр
    char buffer[1024];
    sprintf(buffer, sql, k, p);
    sqlite3_prepare_v2(pensioners->db, buffer, -1, &stmt, NULL);
    int status;
    *count = 0;
    while (1) {
        status = sqlite3_step(stmt);

        if (status == SQLITE_ROW) {

            pensionerPersistantPtr = realloc(pensionerPersistantPtr, (*count + 1) * sizeof(pensioner_t));

            pensionerPersistantPtr[*count].id = sqlite3_column_int(stmt, 0);
            strcpy(pensionerPersistantPtr[*count].name, (char *)sqlite3_column_text(stmt, 1));
            strcpy(pensionerPersistantPtr[*count].surname, (char *)sqlite3_column_text(stmt, 2));

            sscanf((char *)sqlite3_column_text(stmt, 3), "%i-%i-%i", &pensionerPersistantPtr[*count].birthdate.tm_year, &pensionerPersistantPtr[*count].birthdate.tm_mon, &pensionerPersistantPtr[*count].birthdate.tm_mday);
            pensionerPersistantPtr[*count].birthdate.tm_year -= 1900;
            pensionerPersistantPtr[*count].birthdate.tm_mon -= 1;

            pensionerPersistantPtr[*count].pension = sqlite3_column_double(stmt, 4);
            pensionerPersistantPtr[*count].experience = sqlite3_column_int(stmt, 5);

            ++(*count);
        } else
            break;
    }

    *pensionerArray = pensionerPersistantPtr;

    sqlite3_finalize(stmt);
}

void pensioners_delete(pensioners_t *pensioners) {
    sqlite3_close(pensioners->db);
    free(pensioners);
}
