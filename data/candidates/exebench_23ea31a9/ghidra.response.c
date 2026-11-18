char * jstrescapecpy(char *pt,char *spt)

{
  char cVar1;
  int j;
  int i;
  char *spt_local;
  char *pt_local;
  
  i = 0;
  j = 0;
  if (spt == (char *)0x0) {
    *pt = '\0';
  }
  else {
    for (; spt[i] != '\0'; i = i + 1) {
      cVar1 = spt[i];
      if (cVar1 == '%') {
        pt[j] = '_';
        j = j + 1;
      }
      else if (cVar1 == '\'') {
        pt[j] = '\\';
        pt[j + 1] = spt[i];
        j = j + 2;
      }
      else if (cVar1 == '\\') {
        pt[j] = '\\';
        pt[j + 1] = spt[i];
        j = j + 2;
      }
      else {
        pt[j] = spt[i];
        j = j + 1;
      }
    }
    pt[j] = '\0';
  }
  return pt;
}