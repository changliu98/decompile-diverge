int factors(int M,int *arr)

{
  int iVar1;
  int iVar2;
  int m2;
  int m1;
  int mult;
  int num;
  int N;
  int i;
  int *arr_local;
  int M_local;
  
  i = 0;
  N = M;
  while (N % 0x35 == 0) {
    N = N / 0x35;
    arr[i] = 0x35;
    i = i + 1;
  }
  while (N % 0x2f == 0) {
    N = N / 0x2f;
    arr[i] = 0x2f;
    i = i + 1;
  }
  while (N % 0x2b == 0) {
    N = N / 0x2b;
    arr[i] = 0x2b;
    i = i + 1;
  }
  while (N % 0x29 == 0) {
    N = N / 0x29;
    arr[i] = 0x29;
    i = i + 1;
  }
  while (N % 0x25 == 0) {
    N = N / 0x25;
    arr[i] = 0x25;
    i = i + 1;
  }
  while (N % 0x1f == 0) {
    N = N / 0x1f;
    arr[i] = 0x1f;
    i = i + 1;
  }
  while (N % 0x1d == 0) {
    N = N / 0x1d;
    arr[i] = 0x1d;
    i = i + 1;
  }
  while (N % 0x17 == 0) {
    N = N / 0x17;
    arr[i] = 0x17;
    i = i + 1;
  }
  while (N % 0x13 == 0) {
    N = N / 0x13;
    arr[i] = 0x13;
    i = i + 1;
  }
  while (N % 0x11 == 0) {
    N = N / 0x11;
    arr[i] = 0x11;
    i = i + 1;
  }
  while (N % 0xd == 0) {
    N = N / 0xd;
    arr[i] = 0xd;
    i = i + 1;
  }
  while (N % 0xb == 0) {
    N = N / 0xb;
    arr[i] = 0xb;
    i = i + 1;
  }
  while (N % 8 == 0) {
    N = N / 8;
    arr[i] = 8;
    i = i + 1;
  }
  while (N % 7 == 0) {
    N = N / 7;
    arr[i] = 7;
    i = i + 1;
  }
  while (N % 5 == 0) {
    N = N / 5;
    arr[i] = 5;
    i = i + 1;
  }
  while (N % 4 == 0) {
    N = N / 4;
    arr[i] = 4;
    i = i + 1;
  }
  while (N % 3 == 0) {
    N = N / 3;
    arr[i] = 3;
    i = i + 1;
  }
  while (N % 2 == 0) {
    N = N / 2;
    arr[i] = 2;
    i = i + 1;
  }
  if (0x1f < N) {
    num = 2;
    while (1 < N) {
      iVar1 = num * 6 + -1;
      iVar2 = num * 6 + 1;
      for (; N % iVar1 == 0; N = N / iVar1) {
        arr[i] = iVar1;
        i = i + 1;
      }
      for (; N % iVar2 == 0; N = N / iVar2) {
        arr[i] = iVar2;
        i = i + 1;
      }
      num = num + 1;
    }
  }
  return i;
}