float pluck(float xin, float *bplk)
{
 int ipos;
 float temp, yout;
 bplk[0]++;
 if(*bplk < *(bplk + 1)) {
  ipos = *bplk;
  temp = bplk[ipos];
  bplk[ipos] = xin + *(bplk + 2) * bplk[ipos]
      + *(bplk + 3) * bplk[ipos-1];
  yout = temp;
 } else {
  ipos = 4;
  *bplk = *bplk - *(bplk + 1) + 1.;
  temp = bplk[ipos];
  bplk[ipos] = xin + *(bplk + 2) * bplk[ipos]
      + *(bplk + 3) * bplk[(int)*bplk - 1];
  yout = temp;
 }
 return(yout);
}