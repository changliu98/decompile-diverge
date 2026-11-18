float bpluck(float xin, float *bplk)
{
 int ip;
 float temp;
 bplk[0]++;
 if(*bplk <= bplk[1]) ip = *bplk;
 else {
  ip = 20;
  *bplk = 20;
 }
 bplk[7] = (1. - bplk[8]) * bplk[ip] + bplk[8] * bplk[7];
 temp = bplk[9] * (bplk[2] * bplk[6] + bplk[3] * bplk[ip]);
 bplk[6] = bplk[ip];
 bplk[ip] = bplk[10] * temp + bplk[4] - bplk[10] * bplk[5];
 bplk[5] = bplk[ip] = xin + bplk[ip];
 bplk[4] = temp;
 return(bplk[7]);
}