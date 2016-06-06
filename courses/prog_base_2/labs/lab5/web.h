#ifndef WEB_H
#define WEB_H

#include "pensioners.h"
#include "http_server.h"

int callback (pensioners_t *pensioners, http_method_t http_method, char *url, char *urlParamStr, char *request, char *response);

#endif

