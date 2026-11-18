int func0(int n) {
 int i, j, k, temp;
 int result[3000];
 int primes[3000];
 memset(primes, 0, sizeof(primes));
 int resultIndex = 0;
 for (i = 2; i < 3000; i++) {
  if (primes[i] == 0) {
   primes[i] = 1;
   for (j = i * 2; j < 3000; j += i) {
    primes[j]--;
    if (primes[j] == -3) {
     result[resultIndex] = j;
     resultIndex++;
    }
   }
  }
 }
 for (i = 0; i < resultIndex - 1; i++) {
  for (j = 0; j < resultIndex - i - 1; j++) {
   if (result[j] > result[j + 1]) {
    temp = result[j];
    result[j] = result[j + 1];
    result[j + 1] = temp;
   }
  }
 }
 return result[n - 1];
}