_Bool func0(longlong x)

{
  longlong p;
  longlong x_local;
  _Bool local_9;
  
  if (x % 2 == 0) {
    local_9 = false;
  }
  else if (x == 1) {
    local_9 = true;
  }
  else {
    x_local = x + 1;
    p = 0;
    do {
      if (x_local % 2 != 0) {
        return false;
      }
      x_local = x_local / 2;
      p = p + 1;
    } while (p != x_local);
    local_9 = true;
  }
  return local_9;
}