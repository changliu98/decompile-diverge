char* func0(char* test_list[], int size) {
  static char res[1000];
  strcpy(res, "[");
  for (int i = 0; i < size; i += 2) {
    char temp[100];
    double first, second;
    first = atof(test_list[i]);
    second = atof(test_list[i + 1]);
    snprintf(temp, sizeof(temp), "(%.2f, %.2f)", first, second);
    strcat(res, temp);
    if (i < size - 2) {
      strcat(res, ", ");
    }
  }
  strcat(res, "]");
  return res;
}