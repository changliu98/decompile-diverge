bool _is_self_describing(int n) {
  int i, m, count;
  for (i = 0; i < 10; i++) {
    m = n;
    count = 0;
    while (m > 0) {
      if (m % 10 == i) count++;
      if (count > i) return false;
      m /= 10;
    }
  }
  return true;
}