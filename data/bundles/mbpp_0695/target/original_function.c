bool func0(int test_tup1[], int test_tup2[], int length) {
  for (int i = 0; i < length; i++) {
    if (!(test_tup1[i] < test_tup2[i])) {
      return false;
    }
  }
  return true;
}