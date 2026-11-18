int HPCC_factor235(int n,int *ip)

{
  int *ip_local;
  int n_local;
  int local_c;
  
  ip[2] = 0;
  ip[1] = 0;
  *ip = 0;
  if (((n % 2 == 0) || (n % 3 == 0)) || (n % 5 == 0)) {
    n_local = n;
    if (n < 2) {
      local_c = 1;
    }
    else {
      for (; 1 < n_local && (n_local & 1U) == 0; n_local = n_local >> 1) {
        *ip = *ip + 1;
      }
      for (; 1 < n_local && n_local % 3 == 0; n_local = n_local / 3) {
        ip[1] = ip[1] + 1;
      }
      for (; 1 < n_local && n_local % 5 == 0; n_local = n_local / 5) {
        ip[2] = ip[2] + 1;
      }
      if (n_local == 1) {
        local_c = 0;
      }
      else {
        local_c = 1;
      }
    }
  }
  else {
    local_c = 1;
  }
  return local_c;
}