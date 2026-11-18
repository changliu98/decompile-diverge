char * get_begin(char *nbr,int *sg)

{
  bool bVar1;
  int sign;
  int lp;
  int *sg_local;
  char *nbr_local;
  
  lp = 0;
  sign = 1;
  while( true ) {
    bVar1 = true;
    if (nbr[lp] != '+') {
      bVar1 = nbr[lp] == '-';
    }
    if (!bVar1) break;
    if (nbr[lp] == '-') {
      sign = -sign;
    }
    lp = lp + 1;
  }
  *sg = sign;
  return nbr + lp;
}