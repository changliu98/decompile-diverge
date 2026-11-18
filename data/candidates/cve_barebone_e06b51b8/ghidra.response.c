char * uwsgi_expand_path(char *dir,int dir_len,char *ptr)

{
  char *pcVar1;
  int *piVar2;
  char *dst;
  char src [4097];
  char *ptr_local;
  int dir_len_local;
  char *dir_local;
  char *local_10;
  
  memcpy(src,dir,(long)dir_len);
  src[dir_len] = '\0';
  dst = ptr;
  if (ptr == (char *)0x0) {
    dst = uwsgi_malloc(0x1001);
  }
  pcVar1 = realpath(src,dst);
  if (pcVar1 == (char *)0x0) {
    piVar2 = __errno_location();
    pcVar1 = strerror(*piVar2);
    uwsgi_log("realpath() of %s failed: %s [%s line %d]\n",src,pcVar1,"/work/harness.c",0x41);
    if (ptr == (char *)0x0) {
      free(dst);
    }
    local_10 = (char *)0x0;
  }
  else {
    local_10 = dst;
  }
  return local_10;
}