float catmull_rom_val(int n,float *x,float xval,float *y,float *tangents)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float h11;
  float h01;
  float h10;
  float h00;
  float dx3;
  float dx2;
  float dx;
  float h;
  float m1;
  float m0;
  int i;
  int ival;
  float *tangents_local;
  float *y_local;
  float xval_local;
  float *x_local;
  int n_local;
  
  ival = n + -2;
  i = 0;
  do {
    if (n + -2 <= i) {
LAB_00101257:
      fVar1 = x[ival + 1] - x[ival];
      fVar2 = (xval - x[ival]) / fVar1;
      fVar3 = fVar2 * fVar2;
      fVar4 = fVar2 * fVar3;
      return (float)((double)fVar4 + -(DAT_00102008 * (double)fVar3)) * fVar1 * tangents[ival + 1] +
             (float)(DAT_00102010 * (double)fVar3 - ((double)fVar4 + (double)fVar4)) * y[ival + 1] +
             (float)((double)fVar4 + (double)fVar4 + -(DAT_00102010 * (double)fVar3) + DAT_00102008)
             * y[ival] +
             (float)((double)fVar4 + -(DAT_00102018 * (double)fVar3) + (double)fVar2) * fVar1 *
             tangents[ival];
    }
    if (xval < x[i + 1]) {
      ival = i;
      goto LAB_00101257;
    }
    i = i + 1;
  } while( true );
}