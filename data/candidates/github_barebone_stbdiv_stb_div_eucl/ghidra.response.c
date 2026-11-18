int stb_div_eucl(int v1,int v2)

{
  int r;
  int q;
  int v2_local;
  int v1_local;
  int local_c;
  
  if (v1 < 0) {
    if (v1 == -0x80000000) {
      if (v2 < 0) {
        if (v2 == -0x80000000) {
          q = 1;
          r = 0;
        }
        else {
          q = -(-0x80000000 - v2) / -v2 + 1;
          r = -(-(-0x80000000 - v2) % -v2);
        }
      }
      else {
        q = -1 - -(v2 + -0x80000000) / v2;
        r = -(-(v2 + -0x80000000) % v2);
      }
    }
    else if (v2 < 0) {
      if (v2 == -0x80000000) {
        q = 1;
        r = v1 + -0x80000000;
      }
      else {
        q = -v1 / -v2;
        r = -(-v1 % -v2);
      }
    }
    else {
      q = -(-v1 / v2);
      r = -(-v1 % v2);
    }
  }
  else {
    if (-1 < v2) {
      return v1 / v2;
    }
    if (v2 == -0x80000000) {
      q = 0;
      r = v1;
    }
    else {
      q = -(v1 / -v2);
      r = v1 % -v2;
    }
  }
  if (r < 0) {
    local_c = 1;
    if (0 < v2) {
      local_c = -1;
    }
    local_c = q + local_c;
  }
  else {
    local_c = q;
  }
  return local_c;
}