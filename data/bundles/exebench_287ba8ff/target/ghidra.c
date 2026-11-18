void ft_25_lines(char *s,float *sign,float *val,int *nbr)

{
  int *nbr_local;
  float *val_local;
  float *sign_local;
  char *s_local;
  
  nbr[1] = *s + -0x30;
  if ((-1 < nbr[1]) && (nbr[1] < 10)) {
    if (*nbr == 1) {
      *sign = (float)((double)*sign / DAT_00102010);
    }
    *val = (float)((double)*val * DAT_00102010 + (double)nbr[1]);
  }
  return;
}