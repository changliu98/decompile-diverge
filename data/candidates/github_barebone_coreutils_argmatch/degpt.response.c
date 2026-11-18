ptrdiff_t argmatch(char *arg,char **arglist,void *vallist,size_t valsize)

{
  bool bVar1;
  int iVar2;
  size_t __n;
  size_t sVar3;
  size_t i;
  _Bool ambiguous;
  ptrdiff_t matchind;
  size_t arglen;
  size_t valsize_local;
  void *vallist_local;
  char **arglist_local;
  char *arg_local;
  ptrdiff_t local_10;
  
  __n = strlen(arg);
  matchind = -1;
  bVar1 = false;
  i = 0;
  do {
    if (arglist[i] == (char *)0x0) {
      if (bVar1) {
        local_10 = -2;
      }
      else {
        local_10 = matchind;
      }
      return local_10;
    }
    iVar2 = strncmp(arglist[i],arg,__n);
    if (iVar2 == 0) {
      sVar3 = strlen(arglist[i]);
      if (sVar3 == __n) {
        return i;
      }
      if (matchind == -1) {
        matchind = i;
      }
      else if ((vallist == (void *)0x0) ||
              (iVar2 = memcmp((void *)((long)vallist + valsize * matchind),
                              (void *)((long)vallist + valsize * i),valsize), iVar2 != 0)) {
        bVar1 = true;
      }
    }
    i = i + 1;
  } while( true );
}