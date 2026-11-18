int func0(int L,int R)

{
  int k;
  int i;
  int count;
  int R_local;
  int L_local;
  
  count = 0;
  for (i = L; i <= R; i = i + 1) {
    if ((i < 10) || (0xf < i)) {
      if (0xf < i) {
        for (k = i; k != 0; k = k / 0x10) {
          if (9 < k % 0x10) {
            count = count + 1;
          }
        }
      }
    }
    else {
      count = count + 1;
    }
  }
  return count;
}