char * unmakemask(int mask,char *smask)

{
  bool bVar1;
  int i;
  char *smask_local;
  int mask_local;
  
  bVar1 = (mask & 1U) != 0;
  if (bVar1) {
    *smask = 'c';
  }
  i = (int)bVar1;
  if ((mask & 2U) != 0) {
    smask[i] = 'r';
    i = i + 1;
  }
  if ((mask & 4U) != 0) {
    smask[i] = 'l';
    i = i + 1;
  }
  smask[i] = '\0';
  return smask;
}