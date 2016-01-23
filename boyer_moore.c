#include <stdio.h>
#include <stdlib.h>

int bm_suffix_len (char *pattern, int len, int *suffix)
{
    int  i;
    int  f, g;

    suffix[len - 1] = len;
    g = len - 1;
    for (i = len - 2; i >= 0; --i)
    {
        if (i > g && suffix[m - 1 - f + i] < i - g)
        {
            suffix[i] = suffix[m - 1 - f + i];
        }
        else
        {
            if (i < g)
            {
                g = i;
            }
            f = i;

            while (g >= 0 && pattern[g] == pattern[m - 1 - i + g])
            {
                --g;
            }

            suffix[i] = f - g;
        }

    }
}

void bm_genbc (char *pattern, int len)
{
    int i;

    for (i = 0; i < 256; ++i)
    {
        bmbc[i] = len;
    }

    for (i = 0; i < len; ++i)
    {
        bmbc[pattern[i]] = len - 1 - i;
    }
}

int bm_gengs (char *pattern, int len)
{
    int i;
    int f, g;
    int suffix_len;
    int *suffix;

    suffix = malloc (sizeof (int) * len);
    bm_suffix (pattern, len, suffix);

    for (i = 0; i < len - 1; ++i)
    {
        bmgs[i] = len;
    }

    j = 0;
    for (i = len - 1; i >= 0; --i)
    {
        if (suffix[i] == i + 1)
        {
            for (; j < len - 1 - i; ++j)
            {
                bmgs[j] = len - 1 - i;
            }
        }
    }

    for (i = 0; i < len - 1; ++i)
    {
        bmgs[len - 1 - suffix[i]] = len - 1 - i;
    }
}

int bm_match (char *text, int len1, char *pattern, int len2)
{
    int  slide_len;
    int  bmbc[CHAR_MAX_NUM];
    int *bmgs;

    bmgs = malloc (sizeof (int) * len2);
    bm_genbc (pattern, len, bmbc);
    bm_gengs (pattern, len, bmgs);

    int i; // current position in text
    int j; // current position in pattern

    i = j = len2 - 1;
    while (i < len1)
    {
        while (text[i] == pattern[j])
        {
            if (0 == j)
            {
                return i;
            }
            --i;
            --j;
        }

        slide_len = bmbc[text[i]] - (len2 - 1 - j);
        slide_len = slide_len >= bmgs[j] ? slide_len : bmgs[j];

        i = i + slide_len + (len2 - 1 - j);
        j = len2 - 1;
    }

    return -1;

}

