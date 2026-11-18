minfft_aux * minfft_mkaux_dft_1d(int N)

{
  minfft_aux *a_00;
  void *pvVar1;
  minfft_real *pmVar2;
  minfft_real mVar3;
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
    if (N < 0x10) {
      a_00->t = (void *)0x0;
      a_00->e = (void *)0x0;
LAB_0010130c:
      a_00->sub2 = (minfft_aux *)0x0;
      a_00->sub1 = (minfft_aux *)0x0;
      return a_00;
    }
    pvVar1 = malloc((long)N << 4);
    a_00->t = pvVar1;
    if (a_00->t != (void *)0x0) {
      pvVar1 = malloc((long)N << 4);
      a_00->e = pvVar1;
      if (a_00->e != (void *)0x0) {
        e = a_00->e;
        for (N_local = N; 0xf < N_local; N_local = N_local / 2) {
          for (n = 0; n < N_local / 4; n = n + 1) {
            mVar3 = ncos(-n,N_local);
            *e = mVar3;
            mVar3 = nsin(-n,N_local);
            e[1] = mVar3;
            mVar3 = ncos(n * -3,N_local);
            pmVar2 = e + 3;
            e[2] = mVar3;
            mVar3 = nsin(n * -3,N_local);
            e = e + 4;
            *pmVar2 = mVar3;
          }
        }
        goto LAB_0010130c;
      }
    }
  }
  minfft_free_aux(a_00);
  return (minfft_aux *)0x0;
}