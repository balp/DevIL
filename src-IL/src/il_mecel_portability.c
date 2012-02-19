#ifdef QNX
#include <wchar.h>
int wcsncasecmp(const wchar_t *s1, const wchar_t *s2, size_t n) 
{
    while (n--) 
    {
        wint_t c1 = towlower(*s1);
        wint_t c2 = towlower(*s2);
        wint_t diff = c1 - c2;

        if (diff != 0) 
        {
            return diff;
        }
        if (!c1) 
        {
            return 0;
        }
        ++s1;
        ++s2;
    }
    return 0;
}
#endif

#ifndef _WIN32
#ifdef UNICODE
#include <stdio.h>
#include <wchar.h>
#include <limits.h>

#define UNICODE_CHARS (sizeof(wchar_t) >= 4 ? 0x110000 : 0xFFFE)

size_t wchar2utf8(const wchar_t *srcStr, size_t inputSize, char *dstStr, size_t destSize )
{
    size_t i;
    unsigned char *s = (unsigned char *) dstStr;
    unsigned char *t = s;

    for (i = 0; (i < inputSize) && ((t-s) < destSize); i++)
    {
        wchar_t wc = srcStr[i];
        if (wc <= 0x7F)
        {			/* 7 sig bits */
            *t++ = wc;
        }
        else if (wc <= 0x7FF)
        {			/* 11 sig bits */
            *t++ = 0xC0 | (unsigned char) (wc >> 6);	/* upper 5 bits */
            *t++ = 0x80 | (unsigned char) (wc & 0x3F);	/* lower 6 bits */
        }
        else if (wc <= 0xFFFF)
        {			/* 16 sig bits */
            *t++ = 0xE0 | (unsigned char) (wc >> 12);	/* upper 4 bits */
            *t++ = 0x80 | (unsigned char) ((wc >> 6) & 0x3F);	/* next 6 bits */
            *t++ = 0x80 | (unsigned char) (wc & 0x3F);	/* lowest 6 bits */
        }
        else if (wc < UNICODE_CHARS)
        {			/* 21 sig bits */
            *t++ = 0xF0 | (unsigned char) ((wc >> 18) & 0x07);	/* upper 3 bits */
            *t++ = 0x80 | (unsigned char) ((wc >> 12) & 0x3F);	/* next 6 bits */
            *t++ = 0x80 | (unsigned char) ((wc >> 6) & 0x3F);	/* next 6 bits */
            *t++ = 0x80 | (unsigned char) (wc & 0x3F);	/* lowest 6 bits */
        }
    }
    *t = 0;

    return (t - s);
}

FILE *_wfopen( 
        const wchar_t *filename,
        const wchar_t *mode 
        )
{
    char namebuffer[PATH_MAX];
    char modebuffer[PATH_MAX];
    wchar2utf8(filename, wcslen(filename), namebuffer, sizeof(namebuffer));
    wchar2utf8(filename, wcslen(filename), modebuffer, sizeof(modebuffer));
    return fopen(namebuffer, modebuffer);
}
#endif // UNICODE
#endif // _WIN32
