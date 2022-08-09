#include "../urlencode-share.h"
#include <stdio.h>
#include <errno.h>
#include <getopt.h>

int main (int _argc, char *_argv[]) {

    int            opt;
    char const    *type            = "normal";

    if (_argc > 1 && (!strcmp(_argv[1], "--help") || !strcmp(_argv[1], "-h"))) {
        fputs("urlencode [-t facebook|twitter|whatsapp|linkedin|telegram|instagram] URL\n", stdout);
        return 0;
    }
    
    while((opt = getopt (_argc, _argv, "t:")) != -1) {
        switch (opt) {
        case 't': type = optarg; break;
        case '?':
        default:
            return 1;
        }
    }

    opt = optind;
    char const *url  = (opt<_argc)?_argv[opt++]:NULL;
    char const *arg1 = (opt<_argc)?_argv[opt++]:NULL;
    char const *arg2 = (opt<_argc)?_argv[opt++]:NULL;
    
    if (!strcmp(type, "facebook") && url)
        urlencode_facebook_f(stdout, url);
    else if (!strcmp(type, "twitter") && url)
        urlencode_twitter_f(stdout, url, arg1, arg2);
    else if (!strcmp(type, "whatsapp") && url)
        urlencode_whatsapp_f(stdout, url);
    else if (!strcmp(type, "linkedin") && url)
        urlencode_linkedin_f(stdout, url);
    else if (!strcmp(type, "telegram") && url)
        urlencode_telegram_f(stdout, url, arg1);
    else if (!strcmp(type, "instagram") && url)
        urlencode_instagram_f(stdout, url);
    else if (url)
        urlencode_f(stdout, url);
    else
        return 1;
    
    fputc('\n', stdout);
    return 0;
}
