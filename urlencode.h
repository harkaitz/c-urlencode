#ifndef STR_URLENCODE_H
#define STR_URLENCODE_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>

static __attribute__((unused)) int /* Returns size. */
urlencode (char _o[], size_t _osz, const char _s[])
{
    const char *hex = "0123456789abcdef";
    size_t      sz  = strlen(_s);
    size_t      pos = 0;
    for (size_t i=0; i<sz; i++) {
        if (('a' <= _s[i] && _s[i] <= 'z') ||
            ('A' <= _s[i] && _s[i] <= 'Z') ||
            ('0' <= _s[i] && _s[i] <= '9')) {
            if (pos<_osz) { _o[pos] = _s[i]; }
            pos++;
        } else {
            if (pos<_osz) { _o[pos] = '%';             } pos++;
            if (pos<_osz) { _o[pos] = hex[_s[i] >> 4]; } pos++;
            if (pos<_osz) { _o[pos] = hex[_s[i] & 15]; } pos++;
        }
    }
    if (pos<_osz) _o[pos] = '\0';
    return pos;
}

static __attribute__((unused)) int /* Returns [-1/errno] on output error. */
urlencode_f (FILE *_fp, const char _s[])
{
    const char *hex = "0123456789abcdef";
    size_t      sz  = strlen(_s);
    int         res = 0;
    for (size_t i=0; i<sz; i++) {
        if (('a' <= _s[i] && _s[i] <= 'z') ||
            ('A' <= _s[i] && _s[i] <= 'Z') ||
            ('0' <= _s[i] && _s[i] <= '9')) {
            res = fputc(_s[i], _fp);
            if (res==EOF/*err*/) return -1;
        } else {
            res = fputc('%', _fp);
            if (res==EOF/*err*/) return -1;
            res = fputc(hex[_s[i] >> 4], _fp);
            if (res==EOF/*err*/) return -1;
            res = fputc(hex[_s[i] & 15], _fp);
            if (res==EOF/*err*/) return -1;
        }
    }
    return res;
}

static __attribute__((unused)) int /* Returns size, never fails with enough stack. */
urlencode_fmt_sv(char _o[], size_t _osz, const char *_fmt, va_list _va)
{
    va_list va;
    va_copy(va, _va);
    int blen = vsnprintf(NULL, 0, _fmt, va);
    va_end(va);
    char b[blen+1];
    vsprintf(b, _fmt, _va);
    return urlencode(_o, _osz, b);
}

static __attribute__((unused)) int /* Returns same as `urlencode_fmt_sv()`. */
urlencode_fmt_s(char _o[], size_t _osz, const char *_fmt, ...)
{
    va_list va;
    va_start(va, _fmt);
    int r = urlencode_fmt_sv(_o, _osz, _fmt, va);
    va_end(va);
    return r;
}

static __attribute__((unused)) int /* Returns [-1/errno] on output error. */
urlencode_fmt_fv(FILE *_fp, const char *_fmt, va_list _va)
{
    va_list va;
    int     sz;
    va_copy(va, _va);
    sz = vsnprintf(NULL, 0, _fmt, va);
    va_end(va);
    char b[sz+1];
    vsprintf(b, _fmt, _va);
    return urlencode_f(_fp, b);
}

static __attribute__((unused)) int /* Returns same as urlencode_fmt_fv(). */
urlencode_fmt_f(FILE *_fp, const char *_fmt, ...)
{
    va_list va;
    va_start(va, _fmt);
    int r = urlencode_fmt_fv(_fp, _fmt, va);
    va_end(va);
    return r;
}

static __attribute__((unused)) int /* Returns same as urlencode_fmt_fv(). */
urlencode_post_fv(FILE *_fp, bool _is_url, const char *_fmt, va_list va) {
    bool    is_url = _is_url;
    size_t  fmtsz = strlen(_fmt)+1;
    char    fmt[fmtsz];
    char   *p1,*p2,c;
    int     res = 0, shift;
    memcpy(fmt, _fmt, fmtsz);
    for (p1=fmt, p2=fmt, c=*p2; 1; p2++, c=*p2) {
        if (is_url) {
            if (c=='?'||c=='\0') {
                *p2 = '\0';
                shift = vfprintf(_fp, p1, va);
                if (shift < 0/*err*/) { res = -1; break; }
                res += shift;
                if (c!='\0') {
                    shift = fputc(c, _fp);
                    if (shift==EOF/*err*/) { res = -1; break; }
                    res += 1;
                    p1 = p2+1;
                }
                is_url = false;
            }
        } else if (c=='='||c=='&'||c=='\0'||c=='?') { 
            *p2 = '\0';
            shift = urlencode_fmt_fv(_fp, p1, va);
            if (shift < 0/*err*/) { res = -1; break; }
            res += shift;
            if (c!='\0') {
                shift = fputc(c, _fp);
                if (shift==EOF/*err*/) { res = -1; break; }
                res += 1;
                p1 = p2+1;
            }
        }
        if (c=='\0') break;
    }
    return res;
}

static __attribute__((unused)) int /* Returns same as urlencode_fmt_fv(). */
urlencode_post_f(FILE *_fp, bool _is_url, const char *_fmt, ...) {
    va_list va;
    va_start(va, _fmt);
    int r = urlencode_post_fv(_fp, _is_url, _fmt, va);
    va_end(va);
    return r;
}

#endif
/**l*
 * 
 * MIT License
 * 
 * Bug reports, feature requests to gemini|https://harkadev.com/oss
 * Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **l*/
