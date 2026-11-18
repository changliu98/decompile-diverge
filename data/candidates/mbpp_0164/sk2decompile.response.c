bool isAmicable(int a, int b) {
  int aSum = divSum(a);
  int bSum = divSum(b);
  if (aSum == bSum) {
    return true;
  } else {
    return false;
  }
}