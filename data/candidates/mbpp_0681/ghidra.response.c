int func0(int n)

{
  int i;
  int n_local;
  int local_c;
  
  if (n % 2 == 0) {
    local_c = 2;
  }
  else {
    for (i = 3; local_c = n, i * i <= n; i = i + 2) {
      if (n % i == 0) {
        return i;
      }
    }
  }
  return local_c;
}