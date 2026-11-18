void func0(int number, int need, int remaining, int *result) {
  if (need <= remaining) {
    result[0] = number + need;
    result[1] = remaining - need;
  } else {
    result[0] = number + remaining;
    result[1] = 0;
  }
}