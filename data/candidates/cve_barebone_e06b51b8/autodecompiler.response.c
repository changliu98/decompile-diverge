char *uwsgi_expand_path(char *buf, int len, char *orig) {
 char tbuf[4096];
 memcpy(tbuf, buf, len);
 tbuf[len] = 0;

 char *tmp = orig;
 if (!tmp) tmp = uwsgi_malloc(4096 + 1);
 if (realpath(tbuf, tmp) == NULL) {
  uwsgi_log("realpath() of %s failed: %s [%s line %d]\n", tbuf, strerror(*___errno_location()), "harness.c", 65);;
  if (!orig) free(tmp);
  tmp = NULL;
 }
 else {
  tmp = uwsgi_concat2(tbuf, "\0");
 }

 return tmp;
}