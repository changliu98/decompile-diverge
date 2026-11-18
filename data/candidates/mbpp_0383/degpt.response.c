int func0(int n)

{
  int temp;
  int count;
  int res;
  int n_local;
  
  res = 0;
  count = 0;
  for (temp = n; 0 < temp; temp = temp >> 1) {
    if (count % 2 == 0) {
      res = res | 1 << ((byte)count & 0x1f);
    }
    count = count + 1;
  }
  return n ^ res;
}