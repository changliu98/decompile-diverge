bool __is_permutation(char **a, char **b, int a_size, int b_size) {
  char *common[100];
  int common_size = 0;
  for (int i = 0; i < a_size; i++) {
    for (int j = 0; j < b_size; j++) {
      if (!strcmp(a[i], b[j])) {
        bool is_new = true;
        for (int k = 0; k < common_size; k++) {
          if (!strcmp(common[k], a[i])) {
            is_new = false;
            break;
          }
        }
        if (is_new) {
          common[common_size++] = a[i];
        }
      }
    }
  }
  char *a_common[100];
  char *b_common[100];
  int a_common_size = 0;
  int b_common_size = 0;
  for (int i = 0; i < a_size; i++) {
    for (int j = 0; j < common_size; j++) {
      if (!strcmp(a[i], common[j])) {
        a_common[a_common_size++] = a[i];
      }
    }
  }
  for (int i = 0; i < b_size; i++) {
    for (int j = 0; j < common_size; j++) {
      if (!strcmp(b[i], common[j])) {
        b_common[b_common_size++] = b[i];
      }
    }
  }
  if (a_common_size != b_common_size) {
    return false;
  }
  for (int i = 0; i < a_common_size; i++) {
    if (strcmp(a_common[i], b_common[i])) {
      return false;
    }
  }
  return true;
}