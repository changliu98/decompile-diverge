char * func0(int n)

{
  double dVar1;
  int i;
  int count;
  int n_local;
  char *local_10;
  
  count = 0;
  for (i = 1; dVar1 = sqrt((double)n), i < (int)dVar1 + 2; i = i + 1) {
    if (n % i == 0) {
      if (n / i == i) {
        count = count + 1;
      }
      else {
        count = count + 2;
      }
    }
  }
  if (count % 2 == 0) {
    local_10 = "Even";
  }
  else {
    local_10 = "Odd";
  }
  return local_10;
}