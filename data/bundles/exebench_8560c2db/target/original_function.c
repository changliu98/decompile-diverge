static unsigned int mc_bitcode(float *val, float thres)
{
 unsigned int i, res = 0;

 for(i=0; i<8; i++) {
  if(val[i] > thres) {
   res |= 1 << i;
  }
 }
 return res;
}