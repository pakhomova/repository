#ifndef HTTP_H
#define HTTP_H

#include "socket.h"
#define LENN 256

typedef struct {
    char key[LENN];
    char value[LENN];
} keyvalue_t;

typedef struct htpp_request_s {
    char method[8];
    char uri[LENN];
    keyvalue_t *form;
    int formLength;
} http_request_t;

http_request_t http_request_parse (char *request);
const char *http_request_getArg (http_request_t *self, const char *key);
const char *keyvalue_toString (keyvalue_t *self);

void http_sendHtml (socket_t *client, char *htmlPath);
void http_sendXML (socket_t *client, char *root);

#endif
