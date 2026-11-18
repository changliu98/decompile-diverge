int func0(char **lst,int size)

{
  int iVar1;
  int i;
  int size_local;
  char **lst_local;
  
  i = 1;
  while( true ) {
    if (size <= i) {
      return 1;
    }
    iVar1 = strcmp(*lst,lst[i]);
    if (iVar1 != 0) break;
    i = i + 1;
  }
  return 0;
}