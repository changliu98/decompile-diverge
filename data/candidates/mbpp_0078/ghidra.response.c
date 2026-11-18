int func0(int n)

{
  int ans;
  int i;
  int count;
  int n_local;
  undefined4 local_c;
  
  if (n % 2 == 0) {
    count = 0;
    for (i = 0; i < 0x20; i = i + 1) {
      count = (n >> ((byte)i & 0x1f) & 1U) + count;
    }
    ans = n / 2;
    if (count % 2 != 0) {
      ans = ans + 1;
    }
    local_c = ans;
  }
  else {
    local_c = (n + 1) / 2;
  }
  return local_c;
}