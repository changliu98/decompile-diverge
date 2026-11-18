char * func0(int *test_tup,int size)

{
  int iVar1;
  char *__s;
  double dVar2;
  char *result_str;
  int i;
  int res;
  int size_local;
  int *test_tup_local;
  
  res = 0;
  for (i = 0; i < size; i = i + 1) {
    iVar1 = test_tup[i];
    dVar2 = pow(DAT_00102008,(double)((size + -1) - i));
    res = (int)((double)iVar1 * dVar2 + (double)res);
  }
  __s = malloc(0xc);
  sprintf(__s,"%d",(ulong)(uint)res);
  return __s;
}