int rfftp_forward(rfftp_plan plan,double *c,double fct)

{
  ulong n_00;
  ulong uVar1;
  ulong ip_00;
  double *pdVar2;
  double *__ptr;
  long lVar3;
  ulong ido_00;
  double *tmp__1;
  double *tmp_;
  size_t ido;
  size_t ip;
  size_t k;
  size_t k1;
  double *p2;
  double *p1;
  double *ch;
  size_t nf;
  size_t l1;
  size_t n;
  double fct_local;
  double *c_local;
  rfftp_plan plan_local;
  int local_c;
  
  if (plan->length == 1) {
    local_c = 0;
  }
  else {
    n_00 = plan->length;
    uVar1 = plan->nfct;
    __ptr = malloc(n_00 << 3);
    if (__ptr == (double *)0x0) {
      local_c = -1;
    }
    else {
      p2 = __ptr;
      p1 = c;
      l1 = n_00;
      for (k1 = 0; pdVar2 = p1, k1 < uVar1; k1 = k1 + 1) {
        lVar3 = (uVar1 - k1) + -1;
        ip_00 = *(ulong *)((long)plan + lVar3 * 0x18 + 0x18);
        ido_00 = n_00 / l1;
        l1 = l1 / ip_00;
        if (ip_00 == 4) {
          radf4(ido_00,l1,p1,p2,*(double **)((long)plan + lVar3 * 0x18 + 0x20));
        }
        else if (ip_00 == 2) {
          radf2(ido_00,l1,p1,p2,*(double **)((long)plan + lVar3 * 0x18 + 0x20));
        }
        else if (ip_00 == 3) {
          radf3(ido_00,l1,p1,p2,*(double **)((long)plan + lVar3 * 0x18 + 0x20));
        }
        else if (ip_00 == 5) {
          radf5(ido_00,l1,p1,p2,*(double **)((long)plan + lVar3 * 0x18 + 0x20));
        }
        else {
          radfg(ido_00,ip_00,l1,p1,p2,*(double **)((long)plan + lVar3 * 0x18 + 0x20),
                *(double **)((long)plan + lVar3 * 0x18 + 0x28));
          p1 = p2;
          p2 = pdVar2;
        }
        pdVar2 = p1;
        p1 = p2;
        p2 = pdVar2;
      }
      copy_and_norm(c,p1,n_00,fct);
      free(__ptr);
      local_c = 0;
    }
  }
  return local_c;
}