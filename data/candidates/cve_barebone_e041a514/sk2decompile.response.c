static int gd2GetHeader(gdIOCtxPtr fp, int *w, int *h, int *t, int *c, int *i,
                        int *nc, int *nf, gdColorPtr **cp) {
  char magic[5];
  int c1;
  int j;
  int ncolors;
  gdColorPtr *colors;
  for (j = 0; j < 4; j++) {
    c1 = gdGetC(fp);
    if (c1 == -1) {
      return 0;
    }
    magic[j] = c1;
  }
  magic[4] = '\0';
  if (!strcmp(magic, "gd2") && gdGetWord(c, fp) == 1 && (*c == 1 || *c == 2) &&
      gdGetWord(w, fp) && gdGetWord(h, fp) && gdGetWord(t, fp) == 1 &&
      *t >= 64 && *t <= 4096 && gdGetWord(i, fp) == 1 &&
      (*i == 1 || *i == 2 || *i == 3 || *i == 4) && gdGetWord(nc, fp) == 1 &&
      gdGetWord(nf, fp) == 1) {
    if (*i == 2 || *i == 4) {
      ncolors = *nc * *nf;
      if (ncolors * 8 > 0) {
        colors = calloc(ncolors * 8, 1);
        for (j = 0; j < ncolors; j++) {
          if (gdGetInt(&colors[j].red, fp) != 1 ||
              gdGetInt(&colors[j].blue, fp) != 1 || colors[j].red < 0 ||
              colors[j].blue < 0) {
            free(colors);
            return 0;
          }
        }
        *cp = colors;
        return 1;
      }
    } else {
      return 1;
    }
  }
  return 0;
}