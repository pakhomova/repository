#include "web.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

#define KEY_LEN 64
#define VALUE_LEN 64
#define BIRTHDATESTR_LEN 64
#define HREFBUFFER_LEN 128
#define BUFFER_LEN 64

typedef struct {  //один параметр юрл
    char key[KEY_LEN];
    char value[VALUE_LEN];
} pair_t;

typedef struct { //параметры юрл
    pair_t *pairs;
    int numberOfPairs;
} url_params_t;

static url_params_t *url_params_parse (char *urlParamsStr) {  //разбиваем строку юрл, котора€ передаетс€, на пары ключ-значение
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

static char *url_params_get (url_params_t *url_params, char *key) { //получаем значение параметра по данному ключу
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

int callback (pensioners_t *pensioners, http_method_t http_method, char *url, char *urlParamStr, char *request, char *response) { //коллбэк обрабатывает различные ситуации(в зависимости от юрл) и на основе этого выполн€ет нужные действи€
    if (strcmp(url, "/api/pensioners") == 0) {
        if (http_method == http_method_get) { //формируем ответ на гет-запрос
            cJSON *json = cJSON_CreateArray();

            pensioner_t *pensionerArray;
            int numberOfpensioners;

            url_params_t *url_params = url_params_parse(urlParamStr);
            char *kStr = url_params_get(url_params, "k");//достаем параметры к и р
            char *pStr = url_params_get(url_params, "p");
            if (kStr && pStr) {//если удачно достали к и р
                int k = atoi(kStr);
                int p = atoi(pStr);

                pensioners_filter(pensioners, &pensionerArray, &numberOfpensioners, k, p);//запускаем  фильтр
            } else
                pensioners_get_all(pensioners, &pensionerArray, &numberOfpensioners);//иначе выводим всех пенсионеров

            url_params_delete(url_params);

            int i;
            for (i = 0; i < numberOfpensioners; ++i) {
                pensioner_t *pensioner = pensionerArray + i;

                cJSON *jsonPen = cJSON_CreateObject();
                cJSON_AddNumberToObject(jsonPen, "id", pensioner->id);
                cJSON_AddStringToObject(jsonPen, "name", pensioner->name);
                cJSON_AddStringToObject(jsonPen, "surname", pensioner->surname);

                char birthdateStr[BIRTHDATESTR_LEN];
                sprintf(birthdateStr, "%i-%i-%i", pensioner->birthdate.tm_year + 1900, pensioner->birthdate.tm_mon + 1, pensioner->birthdate.tm_mday);
                cJSON_AddStringToObject(jsonPen, "birthdate", birthdateStr);

                cJSON_AddNumberToObject(jsonPen, "pension", pensioner->pension);
                cJSON_AddNumberToObject(jsonPen, "experience", pensioner->experience);


                cJSON_AddItemToArray(json, jsonPen);
            }

            strcpy(response, cJSON_Print(json));
            cJSON_Delete(json);

            return 1;
        } else
        if (http_method == http_method_post) {//формируем ответ на пост-запрос
            cJSON *json = cJSON_Parse(request);//парсим запрос
            if (json) {
                cJSON *jsonName = cJSON_GetObjectItem(json, "name");
                cJSON *jsonSurname = cJSON_GetObjectItem(json, "surname");
                cJSON *jsonbirthdate = cJSON_GetObjectItem(json, "birthdate");
                cJSON *jsonPension = cJSON_GetObjectItem(json, "pension");
                cJSON *jsonExperience = cJSON_GetObjectItem(json, "experience");

                if (jsonName && jsonSurname && jsonPension && jsonExperience && jsonbirthdate) {
                        pensioner_t pensioner;
                        strcpy (pensioner.name, jsonName->valuestring);
                        strcpy (pensioner.surname, jsonSurname->valuestring);

                        memset(&pensioner.birthdate, 0, sizeof(struct tm));
                        sscanf(jsonbirthdate->valuestring, "%i-%i-%i", &pensioner.birthdate.tm_year, &pensioner.birthdate.tm_mon, &pensioner.birthdate.tm_mday);
                        pensioner.birthdate.tm_year -= 1900;
                        pensioner.birthdate.tm_mon -= 1;

                        pensioner.experience = jsonExperience->valueint;
                        pensioner.pension = jsonPension->valuedouble;

                        pensioners_insert (pensioners, &pensioner);

                        strcpy (response, "OK");

                        return 1;
                }
            }
            cJSON_Delete(json);
        }
    } else
    if (strncmp(url, "/api/pensioners/", strlen("/api/pensioners/")) == 0) {
        int pensionerId = atoi(strstr(strstr(url + 1, "/") + 1, "/") + 1);//выт€гиваем айди из юрл
        if (http_method == http_method_get) { //формируем ответ на гет-запрос по айди
            pensioner_t *pensioner = pensioners_get (pensioners, pensionerId);
            if (pensioner) {
                cJSON *json = cJSON_CreateObject();
                cJSON_AddNumberToObject(json, "id", pensioner->id);
                cJSON_AddStringToObject(json, "name", pensioner->name);
                cJSON_AddStringToObject(json, "surname", pensioner->surname);

                char birthdateStr[BIRTHDATESTR_LEN];
                sprintf(birthdateStr, "%i-%i-%i", pensioner->birthdate.tm_year + 1900, pensioner->birthdate.tm_mon + 1, pensioner->birthdate.tm_mday);
                cJSON_AddStringToObject(json, "birthdate", birthdateStr);

                cJSON_AddNumberToObject(json, "pension", pensioner->pension);
                cJSON_AddNumberToObject(json, "experience", pensioner->experience);

                strcpy (response, cJSON_Print(json));
                cJSON_Delete(json);

                return 1;
            }
        } else
        if (http_method == http_method_delete) { //формируем ответ на делит-запрос по айди
            if (pensioners_remove(pensioners, pensionerId)) {
                strcpy (response, "OK");
                return 1;
            }
        }
    } else
    if (strcmp(url, "/") == 0) {//если юрл состоит только из слэша, то выводим главную страницу
        strcpy (response, "<html><body><h1>Hello!</h1><br>");
        strcat (response, "<h2>Navigate to <a href=\"/pensioners\">pensioners list</a></h2><br>");
        strcat (response, "<h2>Navigate to <a href=\"/api/pensioners\">api</a></h2><br>");
        strcat (response, "<body><html>");
        return 1;
    } else
    if (strcmp(url, "/pensioners") == 0) { //если юрл такого вида, то выводим список ссылок на пенсионеров
        if (http_method == http_method_get) {//формируем ответ на гет-запрос
            strcpy (response, "<html><body><h1>Pensioners</h1><br><ul>");

            pensioner_t *pensionerArray;
            int numberOfpensioners;

            url_params_t *url_params = url_params_parse(urlParamStr);
            char *kStr = url_params_get(url_params, "k");
            char *pStr = url_params_get(url_params, "p");
            if (kStr && pStr) {
                int k = atoi(kStr);
                int p = atoi(pStr);

                pensioners_filter(pensioners, &pensionerArray, &numberOfpensioners, k, p);
            } else
                pensioners_get_all(pensioners, &pensionerArray, &numberOfpensioners);

            url_params_delete(url_params);

            int i;
            for (i = 0; i < numberOfpensioners; ++i) {
                const pensioner_t *pensioner = pensionerArray + i;

                strcat(response, "<li>");
                char hrefBuffer[HREFBUFFER_LEN];
                sprintf(hrefBuffer, "<a href=\"/pensioners/%u\">", pensioner->id);
                strcat(response, hrefBuffer);
                strcat(response, pensioner->name);
                strcat(response, " ");
                strcat(response, pensioner->surname);
                strcat(response, "</a>");
                strcat(response, "</li>");
            }

            strcat(response, "</ul>");
            strcat(response, "<h2>Navigate to <a href=\"/new-pensioner\">new pensioner creation page</a></h2>");
            strcat(response, "</body></html>");

            return 1;
        } else
        if (http_method == http_method_post) {//формируем ответ на пост-запрос
            url_params_t *url_params = url_params_parse(request);//разбиваем юрл на пары ключ-значение

            const char *name = url_params_get(url_params, "name");
            const char *surname = url_params_get(url_params, "surname");
            const char *birthdate = url_params_get(url_params, "birthdate");
            const char *pension = url_params_get(url_params, "pension");
            const char *experience = url_params_get(url_params, "experience");

            url_params_delete(url_params);

            pensioner_t pensioner;

            strcpy(pensioner.name, name);
            strcpy(pensioner.surname, surname);
            pensioner.experience = atoi(experience);
            pensioner.pension = atof(pension);

            memset (&pensioner.birthdate, 0, sizeof(struct tm));
            sscanf (birthdate, "%i-%i-%i", &pensioner.birthdate.tm_year, &pensioner.birthdate.tm_mon, &pensioner.birthdate.tm_mday);
            pensioner.birthdate.tm_year -= 1900;
            pensioner.birthdate.tm_mon -= 1;

            pensioners_insert (pensioners, &pensioner);

            strcpy (response, "<html><body><h2>Successfully added</h2><br><h1><a href=\"/pensioners\">Go back</a></h2><br><h2><a href=\"/new-pensioner\">Add new</a></h2></body></html>");//выводим результирующую страничку

            return 1;
        }
    } else
    if (strncmp(url, "/pensioners/", strlen("/pensioners/")) == 0) {
        int pensionerId = atoi(strstr(url + 1, "/") + 1);//вытаскиваем айди пенсионера

        if (http_method == http_method_get) {//формируем ответ на гет-запрос по айди
            pensioner_t *pensioner = pensioners_get(pensioners, pensionerId);
            if (pensioner) {

                strcpy (response, "<html><body><h1>pensioner: ");//формируем хтмл-страницу, выводим информацию про пенсионера
                strcat (response, pensioner->name);
                strcat (response, " ");
                strcat (response, pensioner->surname);
                strcat (response, "</h1><br><ul>");

                char buffer[BUFFER_LEN];

                strcat (response, "<li>");
                strcat (response, "birthdate: ");
                sprintf (buffer, "%i-%i-%i", pensioner->birthdate.tm_year + 1900, pensioner->birthdate.tm_mon + 1, pensioner->birthdate.tm_mday);
                strcat (response, buffer);
                strcat (response, "</li>");

                strcat (response, "<li>");
                strcat (response, "Pension: ");
                sprintf (buffer, "%f", pensioner->pension);
                strcat (response, buffer);
                strcat (response, "</li>");

                strcat (response, "<li>");
                strcat (response, "Experience: ");
                sprintf (buffer, "%u", pensioner->experience);
                strcat (response, buffer);
                strcat (response, "</li>");

                strcat (response, "<form method=\"post\" action=\"");
                strcat (response, url);
                strcat (response, "\"><button type=\"submit\"><h1>Delete</h1></button>");//описываем кнопку делит, котора€ запускает местод пост

                strcat (response, "</body></html>");

                return 1;
            }
        } else
        if (http_method == http_method_post) {//формируем ответ на метод пост(этот метод хапускает кнопка делит)
            if (pensioners_remove(pensioners, pensionerId)) {
                strcpy (response, "<html><body><h2>Successfully deleted</h2><br><h1><a href=\"/pensioners\">Go back</a></h2></body></html>");//выводим страничку успешного удалени€
                return 1;
            }
        }
    } else
    if (strcmp(url, "/new-pensioner") == 0) {//страница добавлени€ нового пенсионера

        strcpy (response, "<html><body><h1>Add new pensioner</h1><br>");
        strcat (response, "<form method=\"post\" action=\"/pensioners\">");
        strcat (response, "Name: <input type=\"text\" name=\"name\"><br><br>");
        strcat (response, "Surname: <input type=\"text\" name=\"surname\"><br><br>");
        strcat (response, "Birthdate: <input type=\"text\" name=\"birthdate\"><br><br>");
        strcat (response, "Pension: <input type=\"text\" name=\"pension\"><br><br>");
        strcat (response, "Experience: <input type=\"text\" name=\"experience\"><br><br>");

        strcat (response, "<button type=\"Submit\">Submit</button>");
        strcat (response, "</form></body></html>");

        return 1;
    }

    return 0;
}

