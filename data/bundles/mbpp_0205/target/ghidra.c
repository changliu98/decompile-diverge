void func0(int *test_tup,int n,int *res)

{
  int i;
  int *res_local;
  int n_local;
  int *test_tup_local;
  
  for (i = 0; i < n; i = i + 1) {
    res[i] = test_tup[i] ^ 0xffffffff;
  }
  return;
}