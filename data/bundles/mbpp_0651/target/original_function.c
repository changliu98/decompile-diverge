bool func0(int test_tup1[], int n1, int test_tup2[], int n2) {
  for (int i = 0; i < n2; i++) {
    bool found = false;
    for (int j = 0; j < n1; j++) {
      if (test_tup2[i] == test_tup1[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      return false;
    }
  }
  return true;
}