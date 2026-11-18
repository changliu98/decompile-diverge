int func0(int n)

{
  int temp;
  int i;
  int cnt;
  int n_local;
  
  cnt = 0;
  for (i = 1; i <= n; i = i + 1) {
    for (temp = i; temp != 0; temp = temp / 2) {
      if (temp % 2 == 0) {
        cnt = cnt + 1;
      }
    }
  }
  return cnt;
}