char* solve(int* c, int c_size) {
  int i;
  for (i = 1; i < c_size; i++) {
    if (c[i] != c[0]) {
      return "NO";
    }
  }
  return "YES";
}