int func0(int n)

{
  int iVar1;
  int temp;
  int j_1;
  int i_1;
  int j;
  int i;
  int resultIndex;
  int result [3000];
  int primes [3000];
  int n_local;
  
  memset(primes,0,12000);
  resultIndex = 0;
  for (i = 2; i < 3000; i = i + 1) {
    if (primes[i] == 0) {
      primes[i] = 1;
      for (j = i << 1; j < 3000; j = i + j) {
        primes[j] = primes[j] + -1;
        if (primes[j] == -3) {
          result[resultIndex] = j;
          resultIndex = resultIndex + 1;
        }
      }
    }
  }
  for (i_1 = 0; i_1 < resultIndex + -1; i_1 = i_1 + 1) {
    for (j_1 = 0; j_1 < (resultIndex - i_1) + -1; j_1 = j_1 + 1) {
      if (result[j_1 + 1] < result[j_1]) {
        iVar1 = result[j_1];
        result[j_1] = result[j_1 + 1];
        result[j_1 + 1] = iVar1;
      }
    }
  }
  return result[n + -1];
}