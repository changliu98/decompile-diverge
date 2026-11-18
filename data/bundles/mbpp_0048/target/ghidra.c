int func0(int n)

{
  int temp;
  int res;
  int count;
  int n_local;
  
  count = 0;
  res = 0;
  for (temp = n; 0 < temp; temp = temp >> 1) {
    if (count % 2 == 0) {
      res = 1 << ((byte)count & 0x1f) | res;
    }
    count = count + 1;
  }
  return n | res;
}