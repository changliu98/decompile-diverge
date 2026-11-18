int func0(int p0, int p1, int p2) {
  int i, is_prime;
  is_prime = p0 >= 2;
  for (i = 2; i * i <= p0; i++) {
    if (p0 % i == 0) {
      is_prime = 0;
    }
  }
  if (is_prime) {
    return p1;
  } else {
    return p2;
  }
}