int func0(int n)

{
  int count;
  int temp;
  int pos;
  int n_local;
  undefined4 local_c;
  
  local_c = n;
  if ((n & n + 1U) != 0) {
    pos = 0;
    count = 0;
    for (temp = n; temp != 0; temp = temp >> 1) {
      if ((temp & 1U) == 0) {
        pos = count;
      }
      count = count + 1;
    }
    local_c = n | 1 << ((byte)pos & 0x1f);
  }
  return local_c;
}