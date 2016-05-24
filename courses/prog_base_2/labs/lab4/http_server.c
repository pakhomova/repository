#include "http_server.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <winsock2.h>

#include "web.h"

#define MESSAGE_404 "HTTP/1.1 404 NOT FOUND\r\nContent-Length: 9\r\n\r\nNOT FOUND"
#define CONTLENSTR_LEN 64
#define PORT 8080

struct http_server_s {
    pensioners_t *pensioners;
};

static int checkHttpRequestCompleteness (const char *request, int size) {//���������, ������ �� ���� ������
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
    if (contentRealLength >= contentLength)//���������, ��������� �� �������� ������ ������� � �������
        return 1;
    return 0;
}

static void parseHttpRequest(const char *request, http_method_t *http_method, char *url, char *message) {//������ ���� ������
    if (http_method) {//���������� ����� ����� � ��������� ���
        *http_method = http_method_get;
        if (strncmp(request, "POST", strlen("POST")) == 0)
            *http_method = http_method_post;
        else if (strncmp(request, "DELETE", strlen("DELETE")) == 0)
            *http_method = http_method_delete;
    }

    if (url) {//�������� ��� � ��������� ��
        char *urlStart = strstr(request, " ") + 1;
        memcpy(url, urlStart, strstr(urlStart, " ") - urlStart);
        url[strstr(urlStart, " ") - urlStart] = '\0';
    }

    if (message) {//�������� ���� ������� � ��������� ���
        char *messageStart = strstr(request, "\r\n\r\n") + 4;
        memcpy(message, messageStart, strlen(request) - (messageStart - request));
        message[strlen(request) - (messageStart - request)] = '\0';
    }
}

void makeHttpResponse(const char *message, char *response) {//������ ����� ������� �� ������� ���������� ��������
    strcpy (response, "HTTP/1.1 200 OK\r\n");
    strcat (response, "Content-length: ");
    char contentLengthStr[CONTLENSTR_LEN];
    sprintf (contentLengthStr, "%u", strlen(message));
    strcat (response, contentLengthStr);
    strcat (response, "\r\n\r\n");
    strcat (response, message);
}

http_server_t *http_server_create (pensioners_t *pensioners) {//������� ��������� ������ �� ������ �����������
    http_server_t *http_server = malloc(sizeof(http_server_t));
    http_server->pensioners = pensioners;
    return http_server;
}

void http_server_start(http_server_t *http_server) {//��������� ������
    //�������������� ���������� ������2
    WSADATA wsa;//������� �����(��������� ��� ���������� ���������� ��� ������������� ������)
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
    serverSockAddr.sin_port = htons(PORT);//����������� ���� � ������(������� ����� ��� ������)

    if (bind(listenSocket, (struct sockaddr *)&serverSockAddr, sizeof(struct sockaddr_in)) == SOCKET_ERROR) {//��������� ����� � �������)
        printf("Bind socket error: %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {//������ ���������� ����� �� ���������
        printf("Listen socket error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        exit(1);
    }

    while (1) {
        SOCKET clientSocket = accept(listenSocket, NULL, NULL);//������� ���������� ����� � ����������� ��� ��������� ����������� ������ ��������� ����������� ������ �� ������� ��������
        if (clientSocket == INVALID_SOCKET) {
            printf("Client socket accept error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            exit(1);
        }

        char recvBuffer[BUFFER_LENGTH];//������� ������ ��� �������� � ��������� ����������
        char sendBuffer[BUFFER_LENGTH];

        int recvTotalSize = 0;//������ ��������� ����������
        while (1) {
            int recvSize = recv(clientSocket, recvBuffer + recvTotalSize, BUFFER_LENGTH - recvTotalSize, 0);//�������� ���������� �� �������
            if (recvSize > 0) {
                recvTotalSize += recvSize;
                if (checkHttpRequestCompleteness(recvBuffer, recvTotalSize))//���������, ��������� �� ������ ������� ����������
                    break;
            } else if (recvSize == 0) {
                break;
            } else {
                printf ("recv error: %d\n", WSAGetLastError());
                closesocket(clientSocket);
                closesocket(listenSocket);
                WSACleanup();
                exit(1);
            }
        }
        recvBuffer[recvTotalSize] = '\0';

        http_method_t http_method;
        char url[MAX_URL_LENGTH];
        char request[BUFFER_LENGTH];
        char response[BUFFER_LENGTH];

        parseHttpRequest(recvBuffer, &http_method, url, request);//���������� �� ���� ������� �����, ��� � ������ � �����
        http_server_callback_t http_server_callback = callback;
        if (!http_server_callback(http_server->pensioners, http_method, url, request, response))//������ ������������ � ���� ����� �� ������;������,���� ����� ������ �� �������� � ���������
            strcpy(sendBuffer, MESSAGE_404);
        else
            makeHttpResponse(response, sendBuffer);//���������� ����� � ����� � ����������, ���� ��� ���������

        int sendTotalSize = 0;
        while (1) {
            int sendSize = send(clientSocket, sendBuffer + sendTotalSize, strlen(sendBuffer) - sendTotalSize, 0);//������ ���������� ����� �������
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

        if (shutdown(clientSocket, SD_SEND) == SOCKET_ERROR) {//���� ����� ������� ���, ��� ��������, �� ��������� ����������
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

void http_server_delete(http_server_t *http_server) {
    free (http_server);
}

