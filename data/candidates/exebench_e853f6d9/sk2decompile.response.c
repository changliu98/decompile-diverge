int summe(int *zahl, int *sum) {
  if (*zahl == 0) {
    return 1;
  } else {
    *sum += *zahl;
    *zahl -= 1;
    if (summe(zahl, sum)) {
      return 1;
    }
  }
}