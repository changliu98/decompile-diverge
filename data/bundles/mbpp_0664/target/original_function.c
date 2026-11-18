int func0(int n) {
  if (n % 2 != 0) {
    printf("Invalid Input\n");
    return -1;
  }
  int sm = 0, count = 0;
  while (n >= 2) {
    count += 1;
    sm += n;
    n -= 2;
  }
  return sm / count;
}