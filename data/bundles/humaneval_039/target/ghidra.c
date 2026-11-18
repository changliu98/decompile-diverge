int func0(int n)

{
  bool bVar1;
  int iVar2;
  int w;
  int isprime;
  int count;
  int m;
  int f2;
  int f1;
  int n_local;
  
  f1 = 1;
  f2 = 2;
  count = 0;
  iVar2 = f2;
  do {
    f2 = iVar2;
    if (n <= count) {
      return 0;
    }
    iVar2 = f1 + f2;
    f1 = f2;
    bVar1 = true;
    for (w = 2; w * w <= f2; w = w + 1) {
      if (f2 % w == 0) {
        bVar1 = false;
        break;
      }
    }
    if (bVar1) {
      count = count + 1;
    }
    if (count == n) {
      return f2;
    }
  } while( true );
}