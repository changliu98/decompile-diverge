int func0(int n)

{
  int iVar1;
  int totalPairs;
  int cnt;
  int powerOf2;
  int n_local;
  
  iVar1 = n + 1;
  cnt = iVar1 / 2;
  for (powerOf2 = 2; powerOf2 <= iVar1; powerOf2 = powerOf2 << 1) {
    cnt = ((iVar1 / powerOf2) / 2) * powerOf2 + cnt;
    if ((iVar1 / powerOf2 & 1U) != 0) {
      cnt = iVar1 % powerOf2 + cnt;
    }
  }
  return cnt;
}