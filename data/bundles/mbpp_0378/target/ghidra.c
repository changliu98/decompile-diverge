void func0(int *test_list,int n,int *result)

{
  int i;
  int *result_local;
  int n_local;
  int *test_list_local;
  
  *result = test_list[n + -1];
  for (i = 1; i < n; i = i + 1) {
    result[i] = test_list[i + -1];
  }
  return;
}