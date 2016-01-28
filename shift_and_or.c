#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

void print_bitmap (int *bitmap, int len)
{
    int i;
    int j;

    for (i = 0; i < 256; ++i)
    {
        if (0 == bitmap[i])
        {
            continue;
        }

        printf ("%c: ", i);
        for (j = len - 1; j >= 0; --j)
        {
            if (bitmap[i] & (1 << j))
            {
                printf ("1 ");
            }
            else
            {
                printf ("0 ");
            }
        }
        printf ("\n");
    }
}

void preprocess (char *pattern, int len, int *bitmap)
{
    int i;
    for (i = 0; i < len; ++i)
    {
        bitmap[pattern[i]] |= (1 << i);
    }

    return;
}

char *search (char *text, int tlen, char *pattern, int plen)
{
    int  i;
    int  D = 0;
    int  bitmap[256];

    memset (bitmap, 0, sizeof (bitmap));
    preprocess (pattern, plen, bitmap);
    print_bitmap (bitmap, plen);

    for (i = 0; i < tlen; ++i)
    {
        D = ((D << 1) + 1) & bitmap[text[i]];
        if (D & (1 << (plen - 1)))
        {
            printf ("find pattern in text!\n");
            return text + (i - plen + 1);
        }
    }
    printf ("can not find pattern in text\n");
    return NULL;
}

int main (int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf (stderr, "Usage: %s <pattern> <text>\n", basename (argv[0]));
        return 1;
    }

    search (argv[2], strlen (argv[2]), argv[1], strlen (argv[1]));
    return 0;
}
