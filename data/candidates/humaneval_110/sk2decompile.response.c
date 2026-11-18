char* is_array_even(int* array1, int len1, int* array2, int len2) {
  int count = 0;
  for (int i = 0; i < len1; i++) {
    if (array1[i] % 2 == 0) {
      count++;
    }
  }
  for (int i = 0; i < len2; i++) {
    if (array2[i] % 2 == 0) {
      count++;
    }
  }
  if (count >= len1) {
    return "true";
  } else {
    return "false";
  }
}