int func0(int list1[], int length) {
  int max_val = 0;
  int result = list1[0];
  for (int i = 0; i < length; i++) {
    int occu = 0;
    for (int j = 0; j < length; j++) {
      if (list1[j] == list1[i]) {
        occu++;
      }
    }
    if (occu > max_val) {
      max_val = occu;
      result = list1[i];
    }
  }
  return result;
}