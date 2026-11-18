int plot_digit_wierd(char digit, float row, float col, float hgt, float h, float *vx, float *vy)
{
  int i,j,k,l,m,n,ii,jj,kk,ll,mm,nn;
  float r,c,rr,cc;
  int num;

  num=0;
  if (digit >= '0' && digit <= '9') {
    ii=plot_digit_wierd::lt[digit-'0'];
    jj=plot_digit_wierd::lt[digit-'0'+1];
    for (i=ii;i<jj;i++) {
      r=row-hgt*(plot_digit_wierd::lb[i]/10);
      c=col-h*(plot_digit_wierd::lb[i]%10);
      if (i != ii) {
 vx[num]=rr;
 vy[num]=cc;
 vx[num+1]=r;
 vy[num+1]=c;
 num+=2;
      }
      rr=r;
      cc=c;
    }
  }
  return num;
}