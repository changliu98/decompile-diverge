int func0(int a, int b, int c)
{
  unsigned char local_0;

  if (a + b > c) {
    if (b + c > a) {
      if (c + a > b) {
        local_0 = 1;
      } else {
        local_0 = 0;
      }
    } else {
      local_0 = 0;
    }
  } else {
    local_0 = 0;
  }

  return local_0;
}