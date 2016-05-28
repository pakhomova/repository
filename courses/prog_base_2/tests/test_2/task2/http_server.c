#include "http_server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <winsock2.h>

#include "web.h"

#define MESSAGE_404 "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 9\r\n\r\nNOT FOUND"
#define CONTLENSTR_LEN 64
#define PORT 5000

static int checkHttpRequestCompleteness (const char *request, int size) {
    char buffer[BUFFER_LENGTH];
    memcpy (buffer, request, size);
    buffer[size] = '\0';
    int i;
    for (i = 0; i < size; ++i)
        buffer[i] = tolower(buffer[i]);

    char *headersEndPos = strstr(buffer, "\r\n\r\n");
    if (!headersEndPos)
        return 0;

    char *contentLengthPos = strstr(buffer, "content-length: ");
    if ((!contentLengthPos) || contentLengthPos > headersEndPos)
        return 1;

    int contentLength = atoi(contentLengthPos + strlen("content-length: "));
    char *bodyStartPos = headersEndPos + strlen("\r\n\r\n");
    int contentRealLength = size - (bodyStartPos - buffer);
    if (contentRealLength >= contentLength)//проверяет, совпадает ли реальная длинна запроса с заданой
        return 1;
    return 0;
}

static void parseHttpRequest(const char *request, char *url, char *message) {//парсим хттп запрос
    if (url) {//выделяем юрл и сохраняем ее
        char *urlStart = strstr(request, " ") + 1;
        memcpy(url, urlStart, strstr(urlStart, " ") - urlStart);
        url[strstr(urlStart, " ") - urlStart] = '\0';
    }

    if (message) {//выделяем тело запроса и сохраняем его
        char *messageStart = strstr(request, "\r\n\r\n") + 4;
        memcpy(message, messageStart, strlen(request) - (messageStart - request));
        message[strlen(request) - (messageStart - request)] = '\0';
    }
}

void makeHttpResponse(const char *message, char *response) {//выдаем ответ клиенту на успешно выполненую операцию
    strcpy (response, "HTTP/1.1 200 OK\r\n");
    strcat (response, "Content-length: ");
    char contentLengthStr[CONTLENSTR_LEN];
    sprintf (contentLengthStr, "%u", strlen(message));
    strcat (response, contentLengthStr);
    strcat (response, "\r\n\r\n");
    strcat (response, message);
}

void http_server_start() {//запускаем сервер
    //инициализируем библиотеку винсок2
    WSADATA wsa;//создаем сокет(структура для сохранения информации при инициализации сокета)
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSA startup failed: %d\n", WSAGetLastError());
        exit(1);
    }

    SOCKET listenSocket;
    if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Create listen socket failed: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    struct sockaddr_in serverSockAddr;
    memset(&serverSockAddr, 0, sizeof(struct sockaddr_in));
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;
    serverSockAddr.sin_port = htons(PORT);//подвязываем порт к сокету(создали адрес для сокета)

    if (bind(listenSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {//связываем сокет с адресом)
        printf("Bind socket error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {//ставим серверский сокет на прослушку
        printf("Listen socket error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }

    while (1) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);//создаем клиентский сокет и присваеваем ему синхронно извлеченный первый ожидающий подключения запрос из очереди запросов
        if (clientSocket == INVALID_SOCKET) {
            printf("Client socket accept error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            exit(1);
        }

        char recvBuffer[BUFFER_LENGTH];//создаем буферы для отправки и получения информации
        char sendBuffer[BUFFER_LENGTH];

        int recvTotalSize = 0;//размер полученой информации
        int empty = 0;
        while (1) {
            int recvSize = recv(clientSocket, recvBuffer + recvTotalSize, BUFFER_LENGTH - recvTotalSize, 0);//получаем информацию от клиента
            if (recvSize > 0) {
                recvTotalSize += recvSize;
                if (checkHttpRequestCompleteness(recvBuffer, recvTotalSize))//проверяем, правильно ли сервер получил информацию
                    break;
            } else if (recvSize == 0) {
                empty = 1;
                break;
            } else {
                printf ("recv error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                closesocket(listenSocket);
                WSACleanup();
                exit(1);
            }
        }

        if (empty == 1) {
            shutdown(clientSocket, SD_SEND);
            closesocket(clientSocket);
            continue;
        }

        recvBuffer[recvTotalSize] = '\0';

        char url[MAX_URL_LENGTH];
        char request[BUFFER_LENGTH];
        char response[BUFFER_LENGTH];

        parseHttpRequest(recvBuffer, url, request);//вытягиваем из хттп запроса метод, юрл и запрос в буфер
        http_server_callback_t http_server_callback = callback;
        if (!http_server_callback(url, request, response))//сервер обрабатывает и дает ответ на запрос;ошибка,если такой запрос не прописан в программе
            strcpy(sendBuffer, MESSAGE_404);
        else
            makeHttpResponse(response, sendBuffer);//записываем ответ в буфер и отправляем, если все правильно

        int sendTotalSize = 0;
        while (1) {
            int sendSize = send(clientSocket, sendBuffer + sendTotalSize, strlen(sendBuffer) - sendTotalSize, 0);//сервер отправляет ответ клиенту
            if (sendSize == SOCKET_ERROR) {
                printf("send error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                closesocket(listenSocket);
                WSACleanup();
                exit(1);
            }

            sendTotalSize += sendSize;
            if (sendTotalSize == strlen(sendBuffer))
                break;
        }

        if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {//если клиен получил все, что запросил, то закрываем соединение
            printf("shutdown client socket error: %d\n", WSAGetLastError());
            closesocket(clientSocket);
            closesocket(listenSocket);
            WSACleanup();
            exit(1);
        }

        closesocket(clientSocket);
    }

    closesocket(listenSocket);
    WSACleanup();
}


