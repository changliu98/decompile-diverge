int func0(int *test_tup1, int *test_tup2, int size){
  int i;
  int res = 1;
  for (i = 0; i < size; i++)
    if (test_tup1[i] > test_tup2[i])
      res = 0;
    else
      res = 1;
  return res;
}