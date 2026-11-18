char* func0(int* test_tup, int size) {
  int res = 0;
  for (int i = 0; i < size; i++) {
    res += test_tup[i] * pow(2, size - 1 - i);
  }
  char* result_str = (char*)malloc(sizeof(char) * 12);
  sprintf(result_str, "%d", res);
  return result_str;
}