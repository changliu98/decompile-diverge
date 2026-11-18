ptrdiff_t argmatch_exact(char *arg,char **arglist)

{
  int iVar1;
  size_t i;
  char **arglist_local;
  char *arg_local;
  
  i = 0;
  while( true ) {
    if (arglist[i] == (char *)0x0) {
      return -1;
    }
    iVar1 = strcmp(arglist[i],arg);
    if (iVar1 == 0) break;
    i = i + 1;
  }
  return i;
}