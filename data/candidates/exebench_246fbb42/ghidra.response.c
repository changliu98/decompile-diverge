int mean3(int a,int b,int c,int white,int *err)

{
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_50;
  int local_4c;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_30;
  int m;
  int *err_local;
  int white_local;
  int c_local;
  int b_local;
  int a_local;
  int local_c;
  
  local_c = (a + b + c) / 3;
  if (err != (int *)0x0) {
    if (a - local_c < 1) {
      local_30 = -(a - local_c);
    }
    else {
      local_30 = a - local_c;
    }
    if (b - local_c < 1) {
      local_38 = -(b - local_c);
    }
    else {
      local_38 = b - local_c;
    }
    if (local_38 < local_30) {
      if (a - local_c < 1) {
        local_3c = -(a - local_c);
      }
      else {
        local_3c = a - local_c;
      }
      local_40 = local_3c;
    }
    else {
      if (b - local_c < 1) {
        local_44 = -(b - local_c);
      }
      else {
        local_44 = b - local_c;
      }
      local_40 = local_44;
    }
    if (c - local_c < 1) {
      local_4c = -(c - local_c);
    }
    else {
      local_4c = c - local_c;
    }
    if (local_4c < local_40) {
      if (a - local_c < 1) {
        local_50 = -(a - local_c);
      }
      else {
        local_50 = a - local_c;
      }
      if (b - local_c < 1) {
        local_58 = -(b - local_c);
      }
      else {
        local_58 = b - local_c;
      }
      if (local_58 < local_50) {
        if (a - local_c < 1) {
          local_5c = -(a - local_c);
        }
        else {
          local_5c = a - local_c;
        }
        local_60 = local_5c;
      }
      else {
        if (b - local_c < 1) {
          local_64 = -(b - local_c);
        }
        else {
          local_64 = b - local_c;
        }
        local_60 = local_64;
      }
      local_68 = local_60;
    }
    else {
      if (c - local_c < 1) {
        local_6c = -(c - local_c);
      }
      else {
        local_6c = c - local_c;
      }
      local_68 = local_6c;
    }
    *err = local_68;
  }
  if (((white <= a) || (white <= b)) || (white <= c)) {
    local_70 = white;
    if (white < local_c) {
      local_70 = local_c;
    }
    local_c = local_70;
  }
  return local_c;
}