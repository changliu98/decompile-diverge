bool func0(int list1[], int size1, int list2[], int size2) {
  bool exist = true;
  for (int i = 0; i < size2; i++) {
    bool found = false;
    for (int j = 0; j < size1; j++) {
      if (list2[i] == list1[j]) {
        found = true;
        break;
      }
    }
    if (!found) {
      exist = false;
      break;
    }
  }
  return exist;
}