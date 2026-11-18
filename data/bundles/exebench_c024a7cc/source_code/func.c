
static void pn_diag_SD_contr(int num_elem, double *in_amp, double *out_amp, double *matr)
{
  do {
    *(out_amp++) += *(matr++) * (*(in_amp++));
  } while(--num_elem);
}
