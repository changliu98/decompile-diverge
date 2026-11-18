void sortVrtx(int *vrtx) {
  int sorted, i, temp;
  do {
    sorted = 1;
    for (i = 1; i < 3; i++) {
      if (vrtx[i - 1] > vrtx[i]) {
        temp = vrtx[i];
        vrtx[i] = vrtx[i - 1];
        vrtx[i - 1] = temp;
        sorted = 0;
      }
    }
  } while (!sorted);
}