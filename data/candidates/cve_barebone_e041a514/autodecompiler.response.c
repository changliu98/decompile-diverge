static int _gd2GetHeader(gdIOCtx *fd, int *cx, int *cy, int *cs, int *version, int *csx, int *csy, char **chunk)
{
 int i;
 int c;
 char buf[5];
 int *cbuf;
 int cbuf_len;
 int n;
 int *pcbuf;

 for (i = 0; i < 5; i++) {
  c = gdGetC(fd);
  if (c == (-1)) {
   goto fail;
  }
  buf[i] = c;
 }
 buf[4] = '\0';
 if (strcmp(buf, "gd2") != 0) {
  goto fail;
 }

 if (gdGetWord(version, fd) != 1) {
  goto fail;
 }

 if (*version != 1 && *version != 2) {
  goto fail;
 }

 if (gdGetWord(cx, fd) == 0) {
  goto fail;
 }

 if (gdGetWord(cy, fd) == 0) {
  goto fail;
 }

 if (gdGetWord(cs, fd) != 1) {
  goto fail;
 }

 if (*cs < 65 || *cs > 4096) {
  goto fail;
 }

 if (gdGetWord(csx, fd) != 1) {
  goto fail;
 }

 if (*csx != 1 && *csx != 2 && *csx != 3 && *csx != 4) {
  goto fail;
 }

 if (gdGetWord(csy, fd) != 1) {
  goto fail;
 }

 if (*csx == 2 || *csx == 4) {

  n = *csx * *csy;
  cbuf_len = n * 2 * sizeof(int);

  if (cbuf_len <= 0) {
   goto fail;
  }

  cbuf = (int *)calloc((size_t)cbuf_len, (size_t)1);

  pcbuf = cbuf;

  for (i = 0; i < n; i++) {
   if (gdGetInt(&pcbuf[0], fd) != 1) {
    free(cbuf);
    goto fail;
   }
   if (gdGetInt(&pcbuf[1], fd) != 1) {
    free(cbuf);
    goto fail;
   }

   if (pcbuf[0] < 0 || pcbuf[1] < 0) {
    free(cbuf);
    goto fail;
   }

   pcbuf += 2;
  }

  *chunk = (char *)cbuf;
 }

 return 1;

fail:
 return 0;
}