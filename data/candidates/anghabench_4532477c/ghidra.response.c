char * unmakemask(int mask,char *smask)

{
  bool bVar1;
  int i;
  char *smask_local;
  int mask_local;
  
  bVar1 = (mask & LUA_MASKCALL) != 0;
  if (bVar1) {
    *smask = 'c';
  }
  i = (int)bVar1;
  if ((mask & LUA_MASKRET) != 0) {
    smask[i] = 'r';
    i = i + 1;
  }
  if ((mask & LUA_MASKLINE) != 0) {
    smask[i] = 'l';
    i = i + 1;
  }
  smask[i] = '\0';
  return smask;
}