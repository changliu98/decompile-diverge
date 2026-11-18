int* func0(char* S, int* returnSize) {
  int* result = NULL;
  int count = 0;
  int max = 0;
  int size = 0;
  for (int i = 0; S[i]; i++) {
    char c = S[i];
    if (c == '(') {
      count++;
      if (count > max) {
        max = count;
      }
    } else if (c == ')') {
      count--;
      if (count == 0) {
        result = realloc(result, (size + 1) * sizeof(int));
        result[size++] = max;
        max = 0;
      }
    }
  }
  *returnSize = size;
  return result;
}