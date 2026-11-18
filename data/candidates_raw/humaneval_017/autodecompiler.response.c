int *mus_parse(char *str, int *length)
{
  char *c;
  int *r = NULL, *t;
  int l, i, j, k, n, sz, len, cap;

  char buf[3];

  r = NULL;
  sz = 0;
  cap = 0;

  memset(buf, 0, sizeof(buf));

  l = strlen(str) + 1;

  c = (char *)malloc(l + 1);
  strcpy(c, str);
  strcat(c, " ");

  for (i = 0; i < l; i++) {
    if (c[i] == ' ') {

      if (!strcmp(buf, "o")) {
        do { if ((sz) == (cap)) { if ((cap) <= 0) (cap) = 4; else (cap) *= 2; (t) = (int *)realloc((r), (cap) * sizeof(int)); (r) = (t); } (r)[(sz)++] = (4); } while (0);
      }

      if (!strcmp(buf, "o|")) {
        do { if ((sz) == (cap)) { if ((cap) <= 0) (cap) = 4; else (cap) *= 2; (t) = (int *)realloc((r), (cap) * sizeof(int)); (r) = (t); } (r)[(sz)++] = (2); } while (0);
      }

      if (!strcmp(buf, ".|")) {
        do { if ((sz) == (cap)) { if ((cap) <= 0) (cap) = 4; else (cap) *= 2; (t) = (int *)realloc((r), (cap) * sizeof(int)); (r) = (t); } (r)[(sz)++] = (1); } while (0);
      }

      strcpy(buf, "");
    }
    else {
      j = strlen(buf);

      if (j < sizeof(buf)) {
        buf[j] = c[i];
        buf[j + 1] = '\0';
      }
    }
  }

  free(c);

  *length = sz;

  return r;
}