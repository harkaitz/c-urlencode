# URLENCODE

urlencode(), urlencode_bv(), urlencode_fv(), urlencode_b(), urlencode_f(),
urlencode_post_f()

# SYNOPSIS

    #include <str/urlencode.h>
    
    /* Raw encoders. */
    int urlencode   (char _o[], size_t _osz, const char *_s);
    int urlencode_f (FILE *_fp, const char _s[]);
    
    /* Encode with printf expansion. (Uses the stack) */
    int urlencode_fmt_sv (char _o[], size_t _osz, const char *_fmt, va_list _va);
    int urlencode_fmt_s  (char _o[], size_t _osz, const char *_fmt, ...);
    int urlencode_fmt_fv (FILE *_fp, const char *_fmt, va_list _va);
    int urlencode_fmt_f  (FILE *_fp, const char *_fmt, ...);
    
    /* Prepare a post. */
    int urlencode_post_fv(FILE *_fp, bool _is_url, const char *_fmt, va_list va);
    int urlencode_post_f (FILE *_fp, bool _is_url, const char *_fmt, ...);

# DESCRIPTION

This functions are used to encode strings to URL encoding. The buffer variants
only fail if there's no enough memory in the stack (see *alloca(3)*). The file
pointer variants return -1 in case of output error.

# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)
# SEE ALSO

**OPEN_MEMSTREAM(3)**, **ALLOCA(3)**

