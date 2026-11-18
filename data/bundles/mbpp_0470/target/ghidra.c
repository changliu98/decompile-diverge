void func0(int *test_tup,int size,int *result)

{
  int i;
  int *result_local;
  int size_local;
  int *test_tup_local;
  
  for (i = 0; i < size + -1; i = i + 1) {
    result[i] = test_tup[i] + test_tup[i + 1];
  }
  return;
}