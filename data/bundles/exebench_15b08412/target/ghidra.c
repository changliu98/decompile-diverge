int div_dbl(unsigned_long *u,unsigned_long v)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  unsigned_long v_local;
  unsigned_long *u_local;
  int local_c;
  
  if ((v == 0) || (v <= u[1])) {
    local_c = 1;
  }
  else {
    auVar2 = *(undefined1 (*) [16])u;
    auVar1._8_8_ = 0;
    auVar1._0_8_ = v;
    *u = SUB168(auVar2 / auVar1,0);
    u[1] = SUB168(auVar2 % auVar1,0);
    local_c = 0;
  }
  return local_c;
}