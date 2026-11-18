static int writefile(const char *filename, Buffer *buf) {
  FILE *fp;
  int ret;
  fp = fopen(filename, "w");
  if (fp == NULL) {
    vLoggingPrintf("open %s:", filename);
    return -1;
  }
  ret = 0;
  if (fwrite(buf->data, 1, buf->len, fp) != buf->len || fflush(fp) != 0) {
    vLoggingPrintf("write %s:", filename);
    ret = -1;
  }
  fclose(fp);
  return ret;
}