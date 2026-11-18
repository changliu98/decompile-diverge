char ** func0(char *planet1,char *planet2,int *returnSize)

{
  int iVar1;
  char **out;
  int temp;
  int m;
  int pos2;
  int pos1;
  char *planets [8];
  int *returnSize_local;
  char *planet2_local;
  char *planet1_local;
  char **local_10;
  
  memcpy(planets,&PTR_s_Mercury_00103d60,0x40);
  pos1 = -1;
  pos2 = -1;
  for (m = 0; iVar1 = pos1, m < 8; m = m + 1) {
    iVar1 = strcmp(planets[m],planet1);
    if (iVar1 == 0) {
      pos1 = m;
    }
    iVar1 = strcmp(planets[m],planet2);
    if (iVar1 == 0) {
      pos2 = m;
    }
  }
  if (((pos1 == -1) || (pos2 == -1)) || (pos1 == pos2)) {
    *returnSize = 0;
    local_10 = (char **)0x0;
  }
  else {
    if (pos2 < pos1) {
      pos1 = pos2;
      pos2 = iVar1;
    }
    *returnSize = (pos2 - pos1) + -1;
    if (*returnSize < 1) {
      *returnSize = 0;
      local_10 = (char **)0x0;
    }
    else {
      local_10 = malloc((long)*returnSize << 3);
      m = pos1;
      while (m = m + 1, m < pos2) {
        local_10[(m - pos1) + -1] = planets[m];
      }
    }
  }
  return local_10;
}