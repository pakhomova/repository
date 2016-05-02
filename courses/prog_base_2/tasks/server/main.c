#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <strings.h>

#include "pensioner.h"
#include "socket.h"
#include "http.h"

#define COUNT 100
#define BUFSIZE 100000
#define XML_FILEPATH "Pensioner.xml"

int main () {
    lib_init();

    socket_t *server = socket_new();
    socket_bind (server, 5000);
    socket_listen (server);

    char buf[BUFSIZE];
    int currPensionersCount = PENCOUNT, i;

    pensioner_t *pensionerSet[COUNT];

    for (i = 0; i < COUNT; i++)
        pensionerSet[i] = pensioner_new();

    xmlParse (pensionerSet, XML_FILEPATH);

    while (1) {
        socket_t *client = socket_accept(server);
        socket_read (client, buf, sizeof(buf));
        printf ("%s", buf);
        http_request_t request = http_request_parse(buf);

        if (!strcmp(request.method, "GET"))
        {
            if (!strcmp(request.uri, "/")) http_sendHtml(client, "html/index.html");
            else if (!strcmp(request.uri, "/pensioners")) {
                char buffer[BUFSIZE] = "";
                char htmlPageContent[BUFSIZE] = "";
                char bufferToWrite[BUFSIZE] = "";

                strcat(htmlPageContent, "<html><title>Pensioners list</title><body><pre>");

                int penCounter;
                for (i = 0, penCounter = 0; i < currPensionersCount; i++) {
                    if (!strcmp(pensionerSet[i]->name, "EMPTY")) continue;
                    sprintf (buffer, "Pensioner %i:\n"
                            "\tname: %s\n"
                            "\tsurname: %s\n"
                            "\tbirthDate: %d-%d-%d\n"
                            "\tpension: %.2f\n"
                            "\texperience: %d\n",
                            (penCounter+1),
                            pensionerSet[i]->name,
                            pensionerSet[i]->surname,
                            pensionerSet[i]->birthDate.tm_year, pensionerSet[i]->birthDate.tm_mon, pensionerSet[i]->birthDate.tm_mday,
                            pensionerSet[i]->pension,
                            pensionerSet[i]->experience);
                    strcat(htmlPageContent, buffer);
                    penCounter++;
                }

                strcat (htmlPageContent, "</pre></body></html>\n");
                sprintf (bufferToWrite,
                        "\nHTTP/1.1 200 OK\n"
                        "Content-Type: text/html\n"
                        "Content-Length: %i\n"
                        "\n%s", strlen(htmlPageContent), htmlPageContent);
                socket_write_string (client, bufferToWrite);
            }
            else if (strstr(request.uri, "/pensioners/")) {
                int id = 0;
                int checkCode = sscanf(request.uri, "/pensioners/%d", &id);

                if (checkCode != 0 && id > 0 && id <= currPensionersCount) {
                    char htmlPageContent[BUFSIZE] = "";
                    char buffer[BUFSIZE] = "";
                    char bufferToWrite[BUFSIZE] = "";

                    strcat(htmlPageContent, "<html><title>Pensioner page</title><body><pre>");

                    if (!strcmp(pensionerSet[id]->name, "EMPTY")) sprintf(buffer, "pensioner with id %i was deleted.", id);
                    else {
                        sprintf (buffer, "Pensioner %i:\n"
                                "\tname: %s\n"
                                "\tsurname: %s\n"
                                "\tbirthDate: %d-%d-%d\n"
                                "\tpension: %.2f\n"
                                "\texperience: %d\n",
                                id,
                                pensionerSet[id - 1]->name,
                                pensionerSet[id - 1]->surname,
                                pensionerSet[id - 1]->birthDate.tm_year, pensionerSet[id - 1]->birthDate.tm_mon, pensionerSet[id - 1]->birthDate.tm_mday,
                                pensionerSet[id - 1]->pension,
                                pensionerSet[id - 1]->experience);
                        strcat(htmlPageContent, buffer);
                    }
                    strcat (htmlPageContent, "</pre></body></html>\n");
                    sprintf (bufferToWrite,
                            "\nHTTP/1.1 200 OK\n"
                            "Content-Type: text/html\n"
                            "Content-Length: %i\n"
                            "\n%s", strlen(htmlPageContent), htmlPageContent);
                    socket_write_string (client, bufferToWrite);
                }
                else http_sendHtml(client, "html/pageNotFound.html");
            }
            else http_sendHtml(client, "html/pageNotFound.html");
        }
        else if (!strcmp(request.method, "DELETE")) {
            int id;
            int checkCode = sscanf(request.uri, "/pensioners/%d", &id);
            if (checkCode != 0 && id > 0 && id <= currPensionersCount) {
                strcpy(pensionerSet[id - 1]->name, "EMPTY");
                strcpy(pensionerSet[id - 1]->surname, "EMPTY");
                pensionerSet[id - 1]->birthDate.tm_year = 0;
                pensionerSet[id - 1]->birthDate.tm_mon = 0;
                pensionerSet[id - 1]->birthDate.tm_mday = 0;
                pensionerSet[id - 1]->pension = 0;
                pensionerSet[id - 1]->experience = 0;

                http_sendHtml(client, "html/pensionerDeleted.html");
            }
            else http_sendHtml(client, "html/pageNotFound.html");
        }
        else if (!strcmp(request.method, "POST")) {
            const char *name = http_request_getArg(&request, "name");
            const char *surname = http_request_getArg(&request, "surname");
            const char *pension = http_request_getArg(&request, "pension");
            const char *experience = http_request_getArg(&request, "experience");

            strcpy (pensionerSet[currPensionersCount-1]->name, name);
            strcpy (pensionerSet[currPensionersCount-1]->surname, surname);
            pensionerSet[currPensionersCount-1]->birthDate.tm_year = 1900;
            pensionerSet[currPensionersCount-1]->birthDate.tm_mon = 10;
            pensionerSet[currPensionersCount-1]->birthDate.tm_mday = 12;
            pensionerSet[currPensionersCount-1]->pension = atof(pension);
            pensionerSet[currPensionersCount-1]->experience = atoi(experience);

            http_sendHtml(client, "html/pensionerAdded.html");

            currPensionersCount++;
        }
        else if (!strcmp(request.method, "KEEPALIVE")) printf ("User did an empty request.");
        else http_sendHtml(client, "html/incorrectMethod.html");

        socket_free(client);
    }

    socket_free(server);
    lib_free();
    return 0;
}
