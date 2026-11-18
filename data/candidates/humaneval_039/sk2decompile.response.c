int _10001stPrime(int n) {
  int prime = 1;
  int next = 2;
  int count = 0;
  int isPrime;
  int i;
  while (count < n) {
    prime = prime + next;
    next = prime;
    isPrime = 1;
    for (i = 2; i * i <= prime; i++) {
      if (prime % i == 0) {
        isPrime = 0;
        break;
      }
    }
    if (isPrime) {
      count++;
    }
    if (count == n) {
      return prime;
    }
  }
  return 0;
}