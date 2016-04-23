#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare (stack_t *a) {
    return stack_getCount(a) > 10;
}

int reaction(stack_t *a, int b) {
    if (b == 0) return -1;
    char *str = (char *)malloc(sizeof(char) * LENSTR);
    strcpy (str, stack_peek(a));
    b = strlen (str);
    while (b > 0) {
        if (stack_pop(a) == NULL) {
                free (str);
                return -1;
        }
        b--;
    }
    free (str);
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
