void initialize_temp(uint *a,uint *t)

{
  int j;
  int i;
  uint *t_local;
  uint *a_local;
  
  j = 0xe;
  for (i = 9; -1 < i; i = i + -1) {
    t[j] = a[i];
    j = j + -1;
  }
  while (j != -1) {
    t[j] = 0;
    j = j + -1;
  }
  return;
}