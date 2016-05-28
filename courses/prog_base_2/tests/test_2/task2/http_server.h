#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUFFER_LENGTH 25000
#define MAX_URL_LENGTH 512

typedef int (*http_server_callback_t)(const char *url, const char *request, char *response);

void http_server_start ();

#endif


