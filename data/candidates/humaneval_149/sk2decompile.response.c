char **func0(char **arr, int n, int *size) {
  *size = 0;
  for (int i = 0; i < n; i++) {
    if (strlen(arr[i]) % 2 == 0) {
      arr[*size] = arr[i];
      (*size)++;
    }
  }
  for (int i = 0; i < *size - 1; i++) {
    for (int j = 0; j < *size - i - 1; j++) {
      unsigned int len1 = strlen(arr[j]);
      unsigned int len2 = strlen(arr[j + 1]);
      if (len1 > len2 || (len1 == len2 && strcmp(arr[j], arr[j + 1]) > 0)) {
        char *temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  char **result = malloc(sizeof(char *) * *size);
  for (int i = 0; i < *size; i++) {
    result[i] = arr[i];
  }
  return result;
}