int func0(int n)

{
  int j;
  int number;
  int factor_count;
  int factors [100];
  int i;
  int n_local;
  
  if (n < 3) {
    return n;
  }
  i = n << 1;
  factor_count = 0;
  for (number = n; 1 < number; number = number + -1) {
    if (n < number * 2) {
      factors[factor_count] = number;
      factor_count = factor_count + 1;
    }
  }
  do {
    for (j = 0; j < factor_count; j = j + 1) {
      if (i % factors[j] != 0) {
        i = n + i;
        break;
      }
      if ((j == factor_count + -1) && (i % factors[j] == 0)) {
        return i;
      }
    }
  } while( true );
}