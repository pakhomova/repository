#include "http_server.h"
#include "pensioners.h"
#include "web.h"

int main() {
    pensioners_t *pensioners = pensioners_create();//������� ������ ������ �����������
    http_server_t *http_server = http_server_create(pensioners);//������� ��������� ������ ��� �����������

    http_server_start (http_server);
    http_server_delete (http_server);

    pensioners_delete (pensioners);

    return 0;
}
