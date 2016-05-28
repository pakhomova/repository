#include "web.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <winsock2.h>
#include "cJSON.h"
#include "../../../tasks/database/database/db_manager.h"
#include "../../../tasks/database/database/pensioner.h"

#define KEY_LEN 64
#define VALUE_LEN 64

typedef struct {
    char key[KEY_LEN];
    char value[VALUE_LEN];
} pair_t;

typedef struct {
    pair_t *pairs;
    int numberOfPairs;
} url_params_t;

static url_params_t *url_params_parse (const char *urlParamsStr) {
    url_params_t *url_params = malloc(sizeof(url_params_t));
    url_params->pairs = malloc(0);
    url_params->numberOfPairs = 0;

    const char *paramStart = urlParamsStr;

    while (1) {
        const char *paramEnd = strchr(paramStart, '&');
        if (!paramEnd)
            paramEnd = strchr(paramStart, '\0');

        const char *equalCh = strchr(paramStart, '=');
        if (equalCh && (equalCh != paramStart) && (equalCh < paramEnd)) {
            pair_t pair;
            memcpy (pair.key, paramStart, equalCh - paramStart);
            pair.key[equalCh - paramStart] = '\0';
            memcpy(pair.value, equalCh + 1, paramEnd - (equalCh + 1));
            pair.value[paramEnd - (equalCh + 1)] = '\0';

            ++url_params->numberOfPairs;
            url_params->pairs = realloc(url_params->pairs, url_params->numberOfPairs * sizeof(pair_t));
            url_params->pairs[url_params->numberOfPairs - 1] = pair;
        }

        if (*paramEnd && *(paramEnd + 1))
            paramStart = paramEnd + 1;
        else
            break;
    }

    return url_params;
}

static const char *url_params_get (url_params_t *url_params, const char *key) {
    int i;
    for (i = 0; i < url_params->numberOfPairs; ++i)
        if (strcmp(url_params->pairs[i].key, key) == 0)
            return url_params->pairs[i].value;
    return NULL;
}

static void url_params_delete (url_params_t *url_params) {
    free (url_params->pairs);
    free (url_params);
}

int callback (const char *url, const char *request, char *response) {

    if (strcmp(url, "/test") == 0) {
        cJSON *myJson = cJSON_CreateObject();

        cJSON_AddStringToObject (myJson, "result", "ok");

        strcpy (response, cJSON_Print(myJson));
        cJSON_Delete (myJson);
        return 1;
    } else
    if (strcmp(url, "/info") == 0) {
        cJSON *myJson = cJSON_CreateObject();

        cJSON_AddStringToObject (myJson, "student", "Zhenya Pakhomova");
        cJSON_AddStringToObject (myJson, "group", "KP-52");
        cJSON_AddNumberToObject (myJson, "variant", 42);

        strcpy (response, cJSON_Print(myJson));
        cJSON_Delete (myJson);
        return 1;
    } else
    if (strcmp(url, "/external") == 0) {
        SOCKET mySocket;
        mySocket = socket(AF_INET, SOCK_STREAM, 0);

        struct sockaddr_in server;
        memset(&server, 0, sizeof(struct sockaddr_in));

        server.sin_addr.s_addr = inet_addr("http://pb-homework.appspot.com/test/var/42?format=json");
        server.sin_family = AF_INET;
        server.sin_port = htons( 80 );

        connect(mySocket , (struct sockaddr *)&server , sizeof(server));

        char message[30];
        strcpy (message, "GET / HTTP/1.1\r\n\r\n");

        send(mySocket , message , strlen(message) , 0);

        recv(mySocket , response , 2000 , 0);

        response += '\0';
        puts(response);

        closesocket(mySocket);

        return 1;
    } else
    if (strcmp(url, "/database-bytes") == 0) {
        cJSON *myJson = cJSON_CreateObject();

        const char *dbFile = "../../../tasks/database/database/database.db";
        db_t *db = db_new(dbFile);

        int db_size = db_getPensionersSize(db);

        cJSON_AddNumberToObject (myJson, "database-bytes", db_size);

        strcpy (response, cJSON_Print(myJson));
        cJSON_Delete (myJson);
        return 1;
    } else
    if (strcmp(url, "/database") == 0) {
        cJSON *myJson = cJSON_CreateArray();

        const char *dbFile = "../../../tasks/database/database/database.db";
        db_t *db = db_new(dbFile);

        pensioner_t *pensioners = malloc (10 * sizeof(pensioner_t));

        int count = db_getPensioners(db, pensioners);

        for (int i = 0; i < count; i++) {
            cJSON *myObject = cJSON_CreateObject();
            cJSON_AddNumberToObject (myObject, "id", pensioners[i].id);
            cJSON_AddStringToObject (myObject, "name", pensioners[i].name);
            cJSON_AddStringToObject (myObject, "surname", pensioners[i].surname);
            cJSON_AddStringToObject (myObject, "birthDate", pensioners[i].birthDate);
            cJSON_AddNumberToObject (myObject, "pension", pensioners[i].pension);
            cJSON_AddNumberToObject (myObject, "experience", pensioners[i].experience);
            cJSON_AddItemToArray(myJson,myObject);
        }

        strcpy (response, cJSON_Print(myJson));
        cJSON_Delete (myJson);
        return 1;
    }


    return 0;
}

