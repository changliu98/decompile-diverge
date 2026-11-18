char *uwsgi_expand_path(char *dir, int dir_len, char *ptr) {
 char path[4096];
 memcpy(path, dir, (size_t) dir_len);
 path[dir_len] = 0;

 if (!ptr)
  ptr = uwsgi_malloc(4096 + 1);

 char *ret = realpath(path, ptr);
 if (!ret) {
  uwsgi_log("realpath() of %s failed: %s [%s line %d]\n", path, strerror((*__errno_location ())), "/work/harness.c", 65);;
  if (!ptr)
   free(ptr);
  return NULL;
 }

 return ptr;
}