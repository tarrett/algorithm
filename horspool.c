#include <stdio.h>
#include <string.h>
#define CSIZE 256

int shift_len[CSIZE];

void horspool_init(char *pattern)
{
  int len;
  int i;

  len = strlen(pattern);
  for (i = 0; i < CSIZE; ++i)
  {
    shift_len[i] = len;
  }
  for (i = 0; i < len - 1; ++i)
  {
    shift_len[pattern[i]] = len - i - 1;
  }

  return;
}

int horspool_match (char *text, char *pattern)
{
  int i, j, end;
  int tlen, plen;

  tlen = strlen(text);
  plen = strlen(pattern);

  horspool_init (pattern);

  for (i = plen - 1, j = plen - 1; i < tlen;)
  {
    end = i;
    while(i >= 0 && j >= 0 && pattern[j] == text[i])
    {
      --i;
      --j;
    }
    if (j < 0)
    {
      return i + 1;
    }

    i = end + shift_len[text[end]];
    j = plen - 1;
  }
  return -1;
}

int main(int argc, char *argv[])
{
  char *pattern;
  char *text;
  int pos;

  if (argc < 3)
  {
    return -1;
  }

  pattern = argv[1];
  text = argv[2];

  pos = horspool_match (text, pattern);
  if (pos >= 0)
  {
    printf ("match at %d (from index 0).\n", pos);
  }
  else
  {
    printf ("not match.\n");
  }

  return 0;

}
