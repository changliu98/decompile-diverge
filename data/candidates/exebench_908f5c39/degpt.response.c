int gcd_ptr(int *u,int *v)

{
  int *piVar1;
  int *t;
  int *v_local;
  int *u_local;
  
  v_local = v;
  u_local = u;
  while (piVar1 = u_local, 0 < *u_local) {
    if (*u_local < *v_local) {
      u_local = v_local;
      v_local = piVar1;
    }
    *u_local = *u_local - *v_local;
  }
  return *v_local;
}