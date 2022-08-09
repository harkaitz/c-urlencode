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

static inline void
urlencode_telegram_f(FILE *_fp, const char _url[], const char _opt_text[]) {
    urlencode_post_f(_fp, true, "https://telegram.me/share/url?url=%s", _url);
    if (_opt_text) {
        fputs("&text=", _fp);
        urlencode_f(_fp, _opt_text);
    }
}

static inline void
urlencode_instagram_f(FILE *_fp, const char _url[]) {
    urlencode_post_f(_fp, true, "https://www.instagram.com/?url=%s", _url);
}

static inline void
urlencode_html_share_with(FILE *_fp, const char _url[], const char _opt_text[], const char _opt_hashtag[],
                          char const *services_and_icons[]) {
    for (size_t i=0; services_and_icons[i]; i+=2) {
        fputs("<a href=\"", _fp);
        if (!strcmp(services_and_icons[i], "facebook"))
            urlencode_facebook_f(_fp, _url);
        else if (!strcmp(services_and_icons[i], "twitter"))
            urlencode_twitter_f(_fp, _url, _opt_text, _opt_hashtag);
        else if (!strcmp(services_and_icons[i], "whatsapp"))
            urlencode_whatsapp_f(_fp, _url);
        else if (!strcmp(services_and_icons[i], "linkedin"))
            urlencode_linkedin_f(_fp, _url);
        else if (!strcmp(services_and_icons[i], "telegram"))
            urlencode_telegram_f(_fp, _url, _opt_text);
        else if (!strcmp(services_and_icons[i], "instagram"))
            urlencode_instagram_f(_fp, _url);
        fputs("\">", _fp);
        if (services_and_icons[i+1][0]) {
            fprintf(_fp, "<img src=\"%s\" alt=\"%s\" style=\"width:32px;\"/>",
                    services_and_icons[i+1],
                    services_and_icons[i]);
        } else {
            fputs(services_and_icons[i], _fp);
        }
        fputs("</a>", _fp);
    }
}


#endif
