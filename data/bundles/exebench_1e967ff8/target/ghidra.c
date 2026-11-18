void right_shift_str(char *p,int n)

{
  char cVar1;
  int iVar2;
  char temp;
  char *q;
  int length_of_str;
  int j;
  int i;
  int n_local;
  char *p_local;
  
  length_of_str = 0;
  for (q = p; *q != '\0'; q = q + 1) {
    length_of_str = length_of_str + 1;
  }
  for (j = 0; j < n; j = j + 1) {
    cVar1 = p[length_of_str + -1];
    iVar2 = length_of_str;
    while (i = iVar2 + -1, 0 < i) {
      p[i] = p[iVar2 + -2];
      iVar2 = i;
    }
    *p = cVar1;
  }
  return;
}