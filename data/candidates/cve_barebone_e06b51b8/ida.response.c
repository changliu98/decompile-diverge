char *__cdecl uwsgi_expand_path(char *dir, int dir_len, char *ptr)
{
  int *v3; // rax
  char *v4; // rax
  char *dst; // [rsp+8h] [rbp-1038h]
  char src[4097]; // [rsp+10h] [rbp-1030h] BYREF
  char *ptra; // [rsp+1020h] [rbp-20h]
  int dir_lena; // [rsp+102Ch] [rbp-14h]
  char *dira; // [rsp+1030h] [rbp-10h]

  dira = dir;
  dir_lena = dir_len;
  ptra = ptr;
  memcpy(src, dir, dir_len);
  src[dir_lena] = 0;
  dst = ptra;
  if ( !ptra )
    dst = (char *)uwsgi_malloc(0x1001uLL);
  if ( realpath(src, dst) )
    return dst;
  v3 = __errno_location();
  v4 = strerror(*v3);
  uwsgi_log("realpath() of %s failed: %s [%s line %d]\n", src, v4, "/work/harness.c", 65LL);
  if ( !ptra )
    free(dst);
  return 0LL;
}