bool func0(int test_tup[], int size) {
  bool res = true;
  int temp[size];
  int temp_size = 0;
  for (int i = 0; i < size; i++) {
    int ele = test_tup[i];
    bool found = false;
    for (int j = 0; j < temp_size; j++) {
      if (temp[j] == ele) {
        found = true;
        break;
      }
    }
    if (found) {
      res = false;
      break;
    }
    temp[temp_size++] = ele;
  }
  return res;
}