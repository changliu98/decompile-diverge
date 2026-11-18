_Bool func0(longlong n)

{
  longlong i;
  longlong n_local;
  _Bool local_9;
  
  if (n < 2) {
    local_9 = false;
  }
  else {
    for (i = 2; i * i - n == 0 || i * i < n; i = i + 1) {
      if (n % i == 0) {
        return false;
      }
    }
    local_9 = true;
  }
  return local_9;
}