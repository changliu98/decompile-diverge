int func0(int s)

{
  int iVar1;
  int k;
  int j;
  int i;
  int maxvalue;
  int s_local;
  
  maxvalue = 0;
  for (i = 1; i < s + -1; i = i + 1) {
    for (j = 1; j < s; j = j + 1) {
      iVar1 = (s - i) - j;
      if (maxvalue < i * j * iVar1) {
        maxvalue = i * j * iVar1;
      }
    }
  }
  return maxvalue;
}