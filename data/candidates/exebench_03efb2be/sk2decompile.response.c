void swap(int *p) {
  int *max, *min;
  int i, j, temp;
  max = p;
  min = p;
  for (i = 0; i < 5; i++) {
    for (j = i; j < 5; j++) {
      if (*max < p[i * 5 + j]) {
        max = p + i * 5 + j;
      }
      if (*min > p[i * 5 + j]) {
        min = p + i * 5 + j;
      }
    }
  }
  temp = p[12];
  p[12] = *max;
  *max = temp;
  *min = *min;
  min = p + 1;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if ((i == 0 && j == 0) || p[i * 5 + j] < *min) {
        min = p + i * 5 + j;
      }
    }
  }
  temp = *min;
  *min = p[4];
  p[4] = temp;
  min = p + 1;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if ((i == 0 && j == 0) || (i == 0 && j == 4) || p[i * 5 + j] < *min) {
        min = p + i * 5 + j;
      }
    }
  }
  temp = *min;
  *min = p[20];
  p[20] = temp;
  min = p + 1;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if ((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0) ||
          p[i * 5 + j] < *min) {
        min = p + i * 5 + j;
      }
    }
  }
  temp = *min;
  *min = p[24];
  p[24] = temp;
}