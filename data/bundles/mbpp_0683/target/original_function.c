bool func0(int n) {
  int i = 1;
  while (i * i <= n) {
    int j = 1;
    while (j * j <= n) {
      if ((i * i + j * j) == n) {
        return true;
      }
      j++;
    }
    i++;
  }
  return false;
}