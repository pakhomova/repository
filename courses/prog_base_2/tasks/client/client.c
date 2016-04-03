#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480
#define SIZE 64

void getIP (struct hostent *remoteHost, const char *host_name, char **ip) {
    remoteHost = gethostbyname(host_name);
	(*ip) = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
	printf("IP address is: %s.\n\n", *ip);
}

void createSocket (SOCKADDR_IN *recvSockAddr, SOCKET *recvSocket, char *ip) {
    memset(recvSockAddr, 0, sizeof(*recvSockAddr));

    recvSockAddr->sin_port = htons(PORT);
    recvSockAddr->sin_family = AF_INET;
    recvSockAddr->sin_addr.s_addr = inet_addr(ip);

	(*recvSocket) = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void sendRequest (const char *host_name, SOCKET *recvSocket, char *typeRequest, char *uri, char *body) {
    char request[200];
    char *str = malloc(SIZE * sizeof(char));
    strcpy (str, "%s %s HTTP/1.1\r\nHost: %s\r\n");
    if (strcmp(typeRequest, "POST") == 0) {
        strcat (str, "Content-length: %d\r\n\r\n");
        strcat (str, body);
        strcat (str, "\r\n\r\n");
        sprintf (request, str, typeRequest, uri, host_name, strlen(body));
    } else {
        strcat (str, "\r\n");
        sprintf (request, str, typeRequest, uri, host_name);
    }

    printf ("%s\n", request);
    send (*recvSocket, request, strlen(request), 0);
    free (str);
}

void receiveResponse (char **buffer, SOCKET *recvSocket) {
    memset (*buffer, 0, MAXBUFLEN);
    recv (*recvSocket, *buffer, MAXBUFLEN, NO_FLAGS_SET);
    printf ("%s\n\n", *buffer);
}

int isVowel (char c) {
    c = tolower(c);
    if (c == 'a' || c == 'o' || c == 'e' || c == 'i' || c == 'u' || c == 'y') return 1;
        else return 0;
}

int main () {
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;

    struct hostent *remoteHost;
    char *ip;
    const char *host_name = "pb-homework.appspot.com";

    char *buffer = malloc(MAXBUFLEN * sizeof(char));

    WSAStartup(MAKEWORD(2, 2), &Data);

	getIP (remoteHost, host_name, &ip);
	createSocket (&recvSockAddr, &recvSocket, ip);
    connect (recvSocket,(SOCKADDR*)&recvSockAddr, sizeof(SOCKADDR_IN));

    char *uri = malloc(SIZE * sizeof(char));
    char *typeRequest = malloc(SIZE * sizeof(char));
    char *body = malloc(SIZE * sizeof(char));

    strcpy (typeRequest, "GET");
    strcpy (uri, "/var/7");

    sendRequest (host_name, &recvSocket, typeRequest, uri, body);
    receiveResponse (&buffer, &recvSocket);

    char *addarg = malloc(SIZE * sizeof(char));
    addarg = strstr(buffer, "secret");

    char *newRequest = malloc(SIZE * sizeof(char));
    strcpy (newRequest, addarg);

    strcat (uri, "?");
    strcat (uri, newRequest);

    sendRequest (host_name, &recvSocket, typeRequest, uri, body);
    receiveResponse (&buffer, &recvSocket);

    addarg = strstr(buffer, "\r\n\r\n");
    addarg += 4;

    int i, count = 0;
    if (isVowel(addarg[0])) count++;
    for (i = 0; i < strlen(addarg) - 1; i++)
        if (addarg[i] == ' ' && isVowel(addarg[i + 1])) count++;

    strcpy (uri, "/var/7");
    strcpy (typeRequest, "POST");
    sprintf (body, "result=%i", count);

    sendRequest (host_name, &recvSocket, typeRequest, uri, body);
    receiveResponse (&buffer, &recvSocket);

    free (newRequest);
    free (typeRequest);
    free (uri);
    free (body);
    free (buffer);
    free (addarg);

    closesocket(recvSocket);
    WSACleanup();

    system("pause");
    return 0;
}
