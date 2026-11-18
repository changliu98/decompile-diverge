char bppm_symbol(float *x)

{
  float *x_local;
  char local_9;
  
  if ((double)*x <= DAT_00102008) {
    if ((double)x[1] <= DAT_00102008) {
      if ((double)x[2] <= DAT_00102008) {
        if (x[1] + x[2] < *x || x[1] + x[2] == *x) {
          if (*x <= x[1] + x[2]) {
            local_9 = ':';
          }
          else {
            local_9 = ',';
          }
        }
        else if ((double)(x[1] / (x[1] + x[2])) <= DAT_00102008) {
          if ((double)(x[2] / (x[1] + x[2])) <= DAT_00102008) {
            local_9 = '|';
          }
          else {
            local_9 = '}';
          }
        }
        else {
          local_9 = '{';
        }
      }
      else {
        local_9 = ')';
      }
    }
    else {
      local_9 = '(';
    }
  }
  else {
    local_9 = '.';
  }
  return local_9;
}