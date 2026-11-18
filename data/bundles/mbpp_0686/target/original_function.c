char *func0(int test_tup[], int size) {
  struct dict freq[100];
  int count = 0;
  for (int i = 0; i < size; i++) {
    int found = 0;
    for (int j = 0; j < count; j++) {
      if (freq[j].key == test_tup[i]) {
        freq[j].value++;
        found = 1;
        break;
      }
    }
    if (!found) {
      freq[count].key = test_tup[i];
      freq[count].value = 1;
      count++;
    }
  }
  char *result = (char *)malloc(1000 * sizeof(char));
  char buffer[50];
  result[0] = '\0';
  strcat(result, "{");
  for (int i = 0; i < count; i++) {
    sprintf(buffer, "%d: %d", freq[i].key, freq[i].value);
    strcat(result, buffer);
    if (i < count - 1) strcat(result, ", ");
  }
  strcat(result, "}");
  return result;
}