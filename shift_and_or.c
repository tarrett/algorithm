#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#define ASIZE 256

void print_int_binary (unsigned int num)
{
    int i;

    for (i = 0; i < 32; ++i)
    {
        if (num & (1 << i))
        {
            printf ("1 ");
        }
        else
        {
            printf ("0 ");
        }
    }
    printf ("\n");
    return;
}

void print_bitmap (int *bitmap, int len)
{
    int i;

    for (i = 0; i < len; ++i)
    {
        if (0 == bitmap[i])
        {
            continue;
        }

        printf ("%c: ", i);
        print_int_binary (bitmap[i]);
    }
}

void sa_preprocess (char *pattern, int len, int *bitmap)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        bitmap[pattern[i]] |= (1 << i);
    }

    return;
}

char *sa_search (char *text, int tlen, char *pattern, int plen)
{
    int  i;
    int  D = 0;
    int  bitmap[ASIZE];

    memset (bitmap, 0, sizeof (bitmap));
    sa_preprocess (pattern, plen, bitmap);
    print_bitmap (bitmap, ASIZE);

    for (i = 0; i < tlen; ++i)
    {
        D = ((D << 1) + 1) & bitmap[text[i]];
        if (D & (1 << (plen - 1)))
        {
            printf ("shift and: find pattern in text!\n");
            return text + (i - plen + 1);
        }
    }
    printf ("can not find pattern in text\n");
    return NULL;
}

void so_preprocess (char *pattern, int plen, int *bitmap)
{
    int i;
    unsigned int mask;

    mask = 1;
    for (i = 0; i < plen; ++i)
    {
        mask <<= 1;
    }
    return;
}

char *so_search (char *text, int tlen, char *pattern, int plen)
{
    int i;
    unsigned int match_mask;
    unsigned int S;
    unsigned int bitmap[ASIZE];

    memset (bitmap, 0, sizeof(bitmap));
    so_preprocess (pattern, plen, bitmap);
    print_bitmap (bitmap, ASIZE);

    match_mask = (1 << (plen - 1));
    for (S = ~0, i = 0; i < tlen; ++i)
    {
        S = (S << 1) | bitmap[text[i]];
        print_int_binary (S);
        if ((~S) & match_mask)
        {
            printf ("shift or: find pattern in text\n");
            return text + (i - plen + 1);
        }
    }
    return NULL;
}

int main (int argc, char *argv[])
{
    char *p;

    if (argc < 3)
    {
        fprintf (stderr, "Usage: %s <pattern> <text>\n", basename (argv[0]));
        return 1;
    }

    p = sa_search (argv[2], strlen (argv[2]), argv[1], strlen (argv[1]));
    printf ("%s\n", NULL == p ? "<null>" : p);
    p = so_search (argv[2], strlen (argv[2]), argv[1], strlen (argv[1]));
    printf ("%s\n", NULL == p ? "<null>" : p);
    return 0;
}
