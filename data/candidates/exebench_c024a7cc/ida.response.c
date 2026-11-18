void __cdecl pn_diag_SD_contr(int num_elem, double *in_amp, double *out_amp, double *matr)
{
  double *v4; // rax
  double v5; // xmm0_8
  double *v6; // rax
  double v7; // xmm2_8
  double *v8; // rax

  do
  {
    v4 = matr++;
    v5 = *v4;
    v6 = in_amp++;
    v7 = *v6;
    v8 = out_amp++;
    *v8 = v5 * v7 + *v8;
    --num_elem;
  }
  while ( num_elem );
}