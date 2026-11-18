int cfftp_comp_twiddle(cfftp_plan plan)

{
  size_t n;
  ulong uVar1;
  double *res;
  ulong uVar2;
  size_t j_1;
  size_t i;
  size_t j;
  size_t ido;
  size_t ip;
  size_t k;
  size_t memofs;
  size_t l1;
  double *twid;
  size_t length;
  cfftp_plan plan_local;
  int local_c;
  
  n = plan->length;
  res = malloc(n << 4);
  if (res == (double *)0x0) {
    local_c = -1;
  }
  else {
    sincos_2pibyn(n,res);
    l1 = 1;
    memofs = 0;
    for (k = 0; k < plan->nfct; k = k + 1) {
      uVar1 = plan->fct[k].fct;
      uVar2 = n / (l1 * uVar1);
      plan->fct[k].tw = plan->mem + memofs;
      memofs = (uVar1 - 1) * (uVar2 - 1) + memofs;
      for (j = 1; j < uVar1; j = j + 1) {
        for (i = 1; i < uVar2; i = i + 1) {
          plan->fct[k].tw[(j - 1) * (uVar2 - 1) + i + -1].r = res[j * 2 * l1 * i];
          plan->fct[k].tw[(j - 1) * (uVar2 - 1) + i + -1].i = res[j * 2 * l1 * i + 1];
        }
      }
      if (0xb < uVar1) {
        plan->fct[k].tws = plan->mem + memofs;
        memofs = uVar1 + memofs;
        for (j_1 = 0; j_1 < uVar1; j_1 = j_1 + 1) {
          plan->fct[k].tws[j_1].r = res[j_1 * 2 * l1 * uVar2];
          plan->fct[k].tws[j_1].i = res[j_1 * 2 * l1 * uVar2 + 1];
        }
      }
      l1 = uVar1 * l1;
    }
    free(res);
    local_c = 0;
  }
  return local_c;
}