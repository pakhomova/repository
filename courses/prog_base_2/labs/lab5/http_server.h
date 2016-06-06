#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUFFER_LENGTH 25000
#define MAX_URL_LENGTH 512

#include "pensioners.h"

typedef struct http_server_s http_server_t;

typedef enum {
    http_method_get,
    http_method_post,
    http_method_delete
} http_method_t;

typedef int (*http_server_callback_t)(pensioners_t *pensioners, http_method_t http_method, char *url, char *urlParamStr, char *request, char *response);

http_server_t *http_server_create (pensioners_t *pensioners);
void http_server_start (http_server_t *http_server);
void http_server_delete (http_server_t *http_server);

#endif


