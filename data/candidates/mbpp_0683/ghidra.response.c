_Bool func0(int n)

{
  int j;
  int i;
  int n_local;
  
  i = 1;
  do {
    if (n < i * i) {
      return false;
    }
    for (j = 1; j * j <= n; j = j + 1) {
      if (i * i + j * j == n) {
        return true;
      }
    }
    i = i + 1;
  } while( true );
}