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

typedef struct {  //���� �������� ���
    char key[KEY_LEN];
    char value[VALUE_LEN];
} pair_t;

typedef struct { //��������� ���
    pair_t *pairs;
    int numberOfPairs;
} url_params_t;

static url_params_t *url_params_parse (char *urlParamsStr) {  //��������� ������ ���, ������� ����������, �� ���� ����-��������
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

static char *url_params_get (url_params_t *url_params, char *key) { //�������� �������� ��������� �� ������� �����
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

int callback (pensioners_t *pensioners, http_method_t http_method, char *url, char *urlParamStr, char *request, char *response) { //������� ������������ ��������� ��������(� ����������� �� ���) � �� ������ ����� ��������� ������ ��������
    if (strcmp(url, "/api/pensioners") == 0) {
        if (http_method == http_method_get) { //��������� ����� �� ���-������
            cJSON *json = cJSON_CreateArray();

            pensioner_t *pensionerArray;
            int numberOfpensioners;

            url_params_t *url_params = url_params_parse(urlParamStr);
            char *kStr = url_params_get(url_params, "k");//������� ��������� � � �
            char *pStr = url_params_get(url_params, "p");
            if (kStr && pStr) {//���� ������ ������� � � �
                int k = atoi(kStr);
                int p = atoi(pStr);

                pensioners_filter(pensioners, &pensionerArray, &numberOfpensioners, k, p);//���������  ������
            } else
                pensioners_get_all(pensioners, &pensionerArray, &numberOfpensioners);//����� ������� ���� �����������

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
        if (http_method == http_method_post) {//��������� ����� �� ����-������
            cJSON *json = cJSON_Parse(request);//������ ������
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
        int pensionerId = atoi(strstr(strstr(url + 1, "/") + 1, "/") + 1);//���������� ���� �� ���
        if (http_method == http_method_get) { //��������� ����� �� ���-������ �� ����
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
        if (http_method == http_method_delete) { //��������� ����� �� �����-������ �� ����
            if (pensioners_remove(pensioners, pensionerId)) {
                strcpy (response, "OK");
                return 1;
            }
        }
    } else
    if (strcmp(url, "/") == 0) {//���� ��� ������� ������ �� �����, �� ������� ������� ��������
        strcpy (response, "<html><body><h1>Hello!</h1><br>");
        strcat (response, "<h2>Navigate to <a href=\"/pensioners\">pensioners list</a></h2><br>");
        strcat (response, "<h2>Navigate to <a href=\"/api/pensioners\">api</a></h2><br>");
        strcat (response, "<body><html>");
        return 1;
    } else
    if (strcmp(url, "/pensioners") == 0) { //���� ��� ������ ����, �� ������� ������ ������ �� �����������
        if (http_method == http_method_get) {//��������� ����� �� ���-������
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
        if (http_method == http_method_post) {//��������� ����� �� ����-������
            url_params_t *url_params = url_params_parse(request);//��������� ��� �� ���� ����-��������

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

            strcpy (response, "<html><body><h2>Successfully added</h2><br><h1><a href=\"/pensioners\">Go back</a></h2><br><h2><a href=\"/new-pensioner\">Add new</a></h2></body></html>");//������� �������������� ���������

            return 1;
        }
    } else
    if (strncmp(url, "/pensioners/", strlen("/pensioners/")) == 0) {
        int pensionerId = atoi(strstr(url + 1, "/") + 1);//����������� ���� ����������

        if (http_method == http_method_get) {//��������� ����� �� ���-������ �� ����
            pensioner_t *pensioner = pensioners_get(pensioners, pensionerId);
            if (pensioner) {

                strcpy (response, "<html><body><h1>pensioner: ");//��������� ����-��������, ������� ���������� ��� ����������
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
                strcat (response, "\"><button type=\"submit\"><h1>Delete</h1></button>");//��������� ������ �����, ������� ��������� ������ ����

                strcat (response, "</body></html>");

                return 1;
            }
        } else
        if (http_method == http_method_post) {//��������� ����� �� ����� ����(���� ����� ��������� ������ �����)
            if (pensioners_remove(pensioners, pensionerId)) {
                strcpy (response, "<html><body><h2>Successfully deleted</h2><br><h1><a href=\"/pensioners\">Go back</a></h2></body></html>");//������� ��������� ��������� ��������
                return 1;
            }
        }
    } else
    if (strcmp(url, "/new-pensioner") == 0) {//�������� ���������� ������ ����������

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

