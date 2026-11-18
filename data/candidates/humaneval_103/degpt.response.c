char * func0(int n,int m)

{
  int iVar1;
  undefined1 *puVar2;
  int index;
  char *out;
  int num;
  int m_local;
  int n_local;
  char *local_10;
  
  if (m < n) {
    local_10 = "-1";
  }
  else {
    num = (m + n) / 2;
    puVar2 = malloc(0x21);
    *puVar2 = 0;
    puVar2[0x20] = 0;
    iVar1 = 0x1f;
    do {
      index = iVar1;
      puVar2[index] = (char)(num % 2) + '0';
      num = num / 2;
      iVar1 = index + -1;
    } while (0 < num);
    local_10 = puVar2 + index;
  }
  return local_10;
}