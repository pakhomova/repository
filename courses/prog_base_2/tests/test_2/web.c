#include "web.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

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
    if (strcmp(url, "/info") == 0) {
        cJSON *myJson = cJSON_CreateObject();

        cJSON_AddStringToObject (myJson, "student", "Zhenya Pakhomova");
        cJSON_AddStringToObject (myJson, "group", "KP-52");
        cJSON_AddNumberToObject (myJson, "variant", 42);

        strcpy (response, cJSON_Print(myJson));
        cJSON_Delete (myJson);
        return 1;
    }
    return 0;
}

