void func0(int *test_tup1,int *test_tup2,int *res,int size)

{
  int i;
  int size_local;
  int *res_local;
  int *test_tup2_local;
  int *test_tup1_local;
  
  for (i = 0; i < size; i = i + 1) {
    res[i] = test_tup1[i] & test_tup2[i];
  }
  return;
}