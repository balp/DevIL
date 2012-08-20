
#ifdef QNX
#include <wchar.h>
int wcsncasecmp(const wchar_t *s1, const wchar_t *s2, size_t n) ;
#endif

#ifndef _WIN32
#ifdef UNICODE
#include <stdio.h>
#include <wchar.h>
#include <limits.h>
size_t wchar2utf8(const wchar_t *srcStr, size_t inputSize, char *dstStr, size_t destSize );
FILE *_wfopen( const wchar_t *filename, const wchar_t *mode );
#endif // UNICODE
#endif // _WIN32
