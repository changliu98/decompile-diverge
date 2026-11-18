int func0(int n) {
  int ans;
  if (n % 2 == 0) {
    int count = 0;
    for (int i = 0; i < 32; i++) {
      count += (n >> i) & 1;
    }
    ans = n / 2;
    if (count % 2 != 0) {
      ans += 1;
    }
  } else {
    ans = (n + 1) / 2;
  }
  return ans;
}