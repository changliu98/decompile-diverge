minfft_aux * minfft_mkaux_realdft_1d(int N)

{
  minfft_aux *a_00;
  void *pvVar1;
  minfft_aux *pmVar2;
  minfft_real *pmVar3;
  minfft_real mVar4;
  minfft_real *e;
  int n;
  minfft_aux *a;
  int N_local;
  
  if ((N < 1) || ((N & N - 1U) != 0)) {
    return (minfft_aux *)0x0;
  }
  a_00 = malloc(0x28);
  if (a_00 != (minfft_aux *)0x0) {
    a_00->N = N;
    if (N < 4) {
      a_00->t = (void *)0x0;
      a_00->e = (void *)0x0;
      a_00->sub1 = (minfft_aux *)0x0;
LAB_001019e8:
      a_00->sub2 = (minfft_aux *)0x0;
      return a_00;
    }
    pvVar1 = malloc((long)(N / 2) << 4);
    a_00->t = pvVar1;
    if (a_00->t != (void *)0x0) {
      pvVar1 = malloc((long)(N / 4) << 4);
      a_00->e = pvVar1;
      if (a_00->e != (void *)0x0) {
        e = a_00->e;
        for (n = 0; n < N / 4; n = n + 1) {
          mVar4 = ncos(-n,N);
          pmVar3 = e + 1;
          *e = mVar4;
          mVar4 = nsin(-n,N);
          e = e + 2;
          *pmVar3 = mVar4;
        }
        pmVar2 = minfft_mkaux_dft_1d(N / 2);
        a_00->sub1 = pmVar2;
        goto LAB_001019e8;
      }
    }
  }
  minfft_free_aux(a_00);
  return (minfft_aux *)0x0;
}