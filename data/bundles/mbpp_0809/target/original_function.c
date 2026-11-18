bool func0(int test_tup1[], int test_tup2[], int size) {
  bool res = true;
  for (int i = 0; i < size; i++) {
    if (!(test_tup1[i] > test_tup2[i])) {
      res = false;
      break;
    }
  }
  return res;
}