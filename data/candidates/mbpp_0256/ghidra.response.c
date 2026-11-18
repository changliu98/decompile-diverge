int func0(int n)

{
  bool bVar1;
  int i;
  int isPrime;
  int num;
  int ctr;
  int n_local;
  
  ctr = 0;
  num = 0;
  do {
    if (n <= num) {
      return ctr;
    }
    if (1 < num) {
      bVar1 = true;
      for (i = 2; i < num; i = i + 1) {
        if (num % i == 0) {
          bVar1 = false;
          break;
        }
      }
      if (bVar1) {
        ctr = ctr + 1;
      }
    }
    num = num + 1;
  } while( true );
}