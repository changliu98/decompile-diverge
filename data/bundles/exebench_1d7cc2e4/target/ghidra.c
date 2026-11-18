void logFibonacci(int n,unsigned_long *fn1,unsigned_long *fn2)

{
  unsigned_long uVar1;
  unsigned_long uVar2;
  unsigned_long uVar3;
  unsigned_long uVar4;
  int n_00;
  long lVar5;
  unsigned_long temp2_1;
  unsigned_long temp1_1;
  unsigned_long temp2;
  unsigned_long temp1;
  int m;
  unsigned_long *fn2_local;
  unsigned_long *fn1_local;
  int n_local;
  
  if (n == 2) {
    *fn2 = 1;
    *fn1 = 1;
  }
  else if (n == 0) {
    *fn2 = 0;
    *fn1 = 0;
  }
  else {
    n_00 = n / 2;
    if (n_00 % 2 == 0) {
      logFibonacci(n_00,fn1,fn2);
      uVar1 = *fn2;
      uVar2 = *fn2;
      uVar3 = *fn1;
      uVar4 = *fn1;
      *fn1 = *fn2 * 2 * *fn1 + *fn1 * *fn1;
      *fn2 = uVar1 * uVar2 + uVar3 * uVar4;
    }
    else {
      logFibonacci(n_00 + -1,fn1,fn2);
      lVar5 = *fn2 * 2 * *fn1 + *fn1 * *fn1;
      *fn2 = lVar5 + *fn2 * *fn2 + *fn1 * *fn1;
      *fn1 = *fn2 + lVar5;
    }
  }
  return;
}