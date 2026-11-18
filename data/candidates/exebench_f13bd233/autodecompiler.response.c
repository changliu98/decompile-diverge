void mtxLoadTranslate(float *m, float x, float y, float z)
{
  m[0]=m[5]=m[10]=m[15]=1;
  m[1]=m[2]=m[3]=m[4]=m[6]=m[7]=m[8]=m[9]=m[11]=0;
  m[12]=x; m[13]=y; m[14]=z;
}