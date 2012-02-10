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
