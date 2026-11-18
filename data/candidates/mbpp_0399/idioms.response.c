void func0(int *test_tup1, int *test_tup2, int *res, int size){
  int i;
  for (i = 0; i < size; i++)
    res[i] = test_tup1[i] ^ test_tup2[i];
}