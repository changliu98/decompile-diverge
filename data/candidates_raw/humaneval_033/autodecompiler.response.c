void sort(int *arr, int len, int *out) {
  int *tmp = (int *)malloc((len / 3 + 1) * sizeof(int));
  int i = 0, j = 0, k = 0, min, t;
  while (1) {
    if (i * 3 < len) {
      tmp[j] = arr[i * 3];
      j++;
      i++;
    } else {
      break;
    }
  }

  for (i = 0; i < j - 1; i++) {
    min = i;
    for (k = i + 1; k < j; k++) {
      if (tmp[k] < tmp[min]) {
        min = k;
      }
    }
    if (min != i) {
      t = tmp[i];
      tmp[i] = tmp[min];
      tmp[min] = t;
    }
  }

  for (i = 0; i < len; i++) {
    if (i % 3 == 0) {
      out[i] = tmp[i / 3];
    } else {
      out[i] = arr[i];
    }
  }
  free(tmp);
}