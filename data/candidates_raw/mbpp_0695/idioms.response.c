int less(int *test_tup1, int *test_tup2, int length){
  int i;
  for(i = 0; i < length; i++){
    if (test_tup1[i] >= test_tup2[i])
      return 0;
  }
  return 1;
}