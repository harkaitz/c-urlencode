#ifndef STR_URLENCODE_SHARE_H
#define STR_URLENCODE_SHARE_H

#include "urlencode.h"

static inline void
urlencode_facebook_f(FILE *_fp, char const _url[]) {
    urlencode_post_f(_fp, true, "https://www.facebook.com/sharer/sharer.php?u=%s", _url);
}

static inline void
urlencode_twitter_f(FILE *_fp, char const _url[], const char _opt_text[], const char _opt_hashtag[]) {
    urlencode_post_f(_fp, true, "https://twitter.com/intent/tweet?url=%s", _url);
    if (_opt_text) {
        fputs("&text=", _fp);
        urlencode_f(_fp, _opt_text);
    }
    if (_opt_hashtag) {
        fputs("&hashtags=", _fp);
        urlencode_f(_fp, _opt_hashtag);
    }
}

static inline void
urlencode_whatsapp_f(FILE *_fp, char const _url[]) {
    urlencode_post_f(_fp, true, "https://api.whatsapp.com/send?text=%s", _url);
}

static inline void
urlencode_linkedin_f(FILE *_fp, const char _url[]) {
    urlencode_post_f(_fp, true, "https://www.linkedin.com/sharing/share-offsite/?url=%s", _url);
}


#endif
