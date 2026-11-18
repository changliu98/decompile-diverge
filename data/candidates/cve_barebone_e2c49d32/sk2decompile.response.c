static int gd2GetHeader(gdIOCtxPtr fp, int *w, int *h, int *ct, int *cl,
                        int *tc, int *tc2, int *tc3, gdPoint **pts) {
  char magic[5];
  int c;
  int i;
  for (i = 0; i < 4; i++) {
    c = gdGetC(fp);
    if (c == -1) {
      return 0;
    }
    magic[i] = c;
  }
  magic[4] = '\0';
  if (strcmp(magic, "gd2") != 0) {
    return 0;
  }
  if (gdGetWord(cl, fp) != 1) {
    return 0;
  }
  if (*cl != 1 && *cl != 2) {
    return 0;
  }
  if (gdGetWord(w, fp) == 0) {
    return 0;
  }
  if (gdGetWord(h, fp) == 0) {
    return 0;
  }
  if (gdGetWord(ct, fp) != 1) {
    return 0;
  }
  if (*ct < 64 || *ct > 4096) {
    return 0;
  }
  if (gdGetWord(tc, fp) != 1) {
    return 0;
  }
  if (*tc != 1 && *tc != 2 && *tc != 3 && *tc != 4) {
    return 0;
  }
  if (gdGetWord(tc2, fp) != 1) {
    return 0;
  }
  if (gdGetWord(tc3, fp) != 1) {
    return 0;
  }
  if (*tc == 2 || *tc == 4) {
    int npts = *tc2 * *tc3;
    gdPoint *p;
    if (overflow2(sizeof(gdPoint), npts) || npts * sizeof(gdPoint) <= 0) {
      return 0;
    }
    p = (gdPoint *)chip::BindingManager::RegisterBoundDeviceContextReleaseHandler(
        npts * sizeof(gdPoint), 1);
    if (p == NULL) {
      return 0;
    }
    for (i = 0; i < npts; i++) {
      if (gdGetInt(&p[i].x, fp) != 1 || gdGetInt(&p[i].y, fp) != 1 ||
          p[i].x < 0 || p[i].y < 0) {
        gdFree(p);
        return 0;
      }
    }
    *pts = p;
  }
  return 1;
}