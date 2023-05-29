#include "../urlencode.h"
#include <stdio.h>
#include <errno.h>

int main (int _argc, char *_argv[]) {

    if (_argc == 1 || !strcmp(_argv[1], "--help") || !strcmp(_argv[1], "-h")) {
        fputs("urlencode URL\n", stdout);
        return 0;
    }
    
    urlencode_f(stdout, _argv[1]);
    fputc('\n', stdout);
    return 0;
}
