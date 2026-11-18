double func0(int x) {
  if (x < 0) {
    exit(1);
  }
  if (x < 3) {
    return 10.5 * x;
  } else {
    return 21 + 4 * (x - 2);
  }
}