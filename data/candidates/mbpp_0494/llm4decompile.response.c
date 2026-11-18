char* func0(int* test_tup, int size) {
 int i;
 int res = 0;
 for (i = 0; i < size; i++) {
  res += test_tup[i] * pow(10, size - 1 - i);
 }
 char* result_str = malloc(12);
 sprintf(result_str, "%d", res);
 return result_str;
}