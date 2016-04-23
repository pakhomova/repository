#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare (stack_t *a) {
    char *str = (char *)malloc (LENSTR * sizeof(char));
    strcpy (str, stack_peek(a));
    if (strstr(str, "pop ") != NULL && strcmp(strstr (str, "pop "), str) == 0) {
        char *num = (char *)malloc (LENSTR * sizeof(char));
        str += 4;
        strcpy (num, str);
        unsigned int i;
        for (i = 0; i < strlen(num); i++)
            if (num[i] < '0' || num[i] > '9') {
                    free (str);
                    free (num);
                    return -1;
            }
        int res = atoi(num);
        free (str);
        free (num);
        return res;
    }
    free (str);
    return -1;
}

int reaction(stack_t *a, int b) {
    if (b == -1) return b;
    while (b > 0) {
        if (stack_pop(a) == NULL) return -1;
        b--;
    }
    return 0;
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
