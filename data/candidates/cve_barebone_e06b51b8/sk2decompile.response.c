char *uwsgi_expand_path(char *path, int len, char *buf) {
  char tmp_path[4096 + 1];
  memcpy(tmp_path, path, len);
  tmp_path[len] = 0;
  char *ret = buf;
  if (!ret) {
    ret = uwsgi_malloc(4096 + 1);
  }
  if (realpath(tmp_path, ret)) {
    return ret;
  }
  uwsgi_log("realpath() of %s failed: %s [%s line %d]\n", tmp_path,
            strerror(errno), "/work/harness.c", 65);
  if (!buf) {
    free(ret);
  }
  return NULL;
}