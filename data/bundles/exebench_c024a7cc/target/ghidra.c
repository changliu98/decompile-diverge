void pn_diag_SD_contr(int num_elem,double *in_amp,double *out_amp,double *matr)

{
  double *matr_local;
  double *out_amp_local;
  double *in_amp_local;
  int num_elem_local;
  
  matr_local = matr;
  out_amp_local = out_amp;
  in_amp_local = in_amp;
  num_elem_local = num_elem;
  do {
    *out_amp_local = *matr_local * *in_amp_local + *out_amp_local;
    num_elem_local = num_elem_local + -1;
    matr_local = matr_local + 1;
    out_amp_local = out_amp_local + 1;
    in_amp_local = in_amp_local + 1;
  } while (num_elem_local != 0);
  return;
}