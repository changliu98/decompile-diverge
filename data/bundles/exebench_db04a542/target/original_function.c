static char *checkpath(char *path, const char *srcpath)
{

 char *p=path;

 if((void *)0!=path && (void *)0!=srcpath) {
  while(*srcpath) {
   if (*srcpath=='\\') {
    *p++ = '/';
    srcpath++;
   }
   else
    *p++ = *srcpath++;
  }
  *p = *srcpath;
 }
 return path;
}