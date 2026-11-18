int uuid_from_str(char *str, int *uuid)
{
  int i; int n; int hit = 0;
  for (i = 0; i < 4; i++)
    uuid[i] = 0;
  for (;;) {
    char c = *str++;
    if (c == '\0')
      return (hit == 32);
    if (c >= '0' && c <= '9')
      n = c - '0';
    else if (c >= 'a' && c <= 'f')
      n = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
      n = c - 'A' + 10;
    else if (strchr(":. -", c))
      continue;
    return (0);
    if (hit < 32) {
      uuid[hit / 8] *= 16;
      uuid[hit / 8] += n;
    }
    hit++;
  }
}