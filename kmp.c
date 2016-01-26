#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_next (char *pattern, int len, int *next)
{
    int i, k;

    next[0] = -1;
    for (i = 1; i < len; ++i)
    {
        k = next[i - 1];
        while (1)
        {
            if (-1 == k || pattern[k] == pattern[i - 1])
            {
                next[i] = k + 1;
                break;
            }
            else
            {
                k = next[k];
            }
        }
    }
}

char *search (char *text, int tlen, char *pattern, int plen)
{
    int *next;
    int  i, j;

    next = (int *) malloc (sizeof (int) * plen);
    if (NULL == next)
    {
        fprintf (stderr, "malloc failed!\n");
        return NULL;
    }

    memset (next, 0, sizeof (int) * plen);
    init_next (pattern, plen, next);

    i = 0;
    j = 0;
    while (i < tlen && j < plen)
    {
        while (i < tlen && j < plen && pattern[j] == text[i])
        {
            ++i;
            ++j;
        }

        if (j >= plen)
        {
            return text + (i - plen);
        }
        else if ( i >= tlen)
        {
            fprintf (stderr, "no pattern in text!\n");
            return NULL;
        }
        else
        {
            j = next[j];
            if (-1 == j)
            {
                ++i;
                ++j;
            }
        }
    }
}

int main (int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf (stderr, "Usage: %s <pattern> <text>\n", argv[0]);
        return 1;
    }

    int i;
    int tlen;
    int plen;
    int *next;

    plen = strlen (argv[1]);
    next = malloc (sizeof (int) * plen);
    init_next (argv[1], plen, next);

    for (i = 0; i < plen; ++i)
    {
        printf ("%d\t", next[i]);
    }
    printf ("\n");

    return 0;
}
