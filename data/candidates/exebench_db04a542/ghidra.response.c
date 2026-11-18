char * checkpath(char *path,char *srcpath)

{
  char *p;
  char *srcpath_local;
  char *path_local;
  
  if ((path != (char *)0x0) && (p = path, srcpath_local = srcpath, srcpath != (char *)0x0)) {
    for (; *srcpath_local != '\0'; srcpath_local = srcpath_local + 1) {
      if (*srcpath_local == '\\') {
        *p = '/';
      }
      else {
        *p = *srcpath_local;
      }
      p = p + 1;
    }
    *p = *srcpath_local;
  }
  return path;
}