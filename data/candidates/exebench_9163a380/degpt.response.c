void rmHSVtoRGB(float h,float s,float v,float *r,float *g,float *b)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float ht;
  float tb;
  float tg;
  float tr;
  float t;
  float q;
  float p;
  float f;
  int i;
  float *b_local;
  float *g_local;
  float *r_local;
  float v_local;
  float s_local;
  float h_local;
  
  tr = 0.0;
  tg = 0.0;
  tb = 0.0;
  if ((v != 0.0) || (NAN(v))) {
    if ((s != 0.0) || (fVar1 = v, fVar2 = v, fVar3 = v, NAN(s))) {
      ht = (float)((double)h * DAT_00102008);
      if (DAT_00102008 <= (double)ht) {
        ht = 0.0;
      }
      iVar4 = (int)ht;
      fVar5 = (float)((double)v * (DAT_00102010 - (double)s));
      fVar6 = (float)((double)v * (DAT_00102010 - (double)(s * (ht - (float)iVar4))));
      fVar7 = (float)((double)v *
                     (-(double)s * (DAT_00102010 - (double)(ht - (float)iVar4)) + DAT_00102010));
      fVar1 = fVar5;
      fVar2 = fVar7;
      fVar3 = v;
      if ((((iVar4 != 0) && (fVar2 = v, fVar3 = fVar6, iVar4 != 1)) &&
          (fVar1 = fVar7, fVar2 = v, fVar3 = fVar5, iVar4 != 2)) &&
         (((fVar1 = v, fVar2 = fVar6, iVar4 != 3 &&
           (fVar1 = v, fVar2 = fVar5, fVar3 = fVar7, iVar4 != 4)) &&
          (fVar1 = tb, fVar2 = tg, fVar3 = tr, iVar4 == 5)))) {
        fVar1 = fVar6;
        fVar2 = fVar5;
        fVar3 = v;
      }
    }
  }
  else {
    tr = 0.0;
    tg = 0.0;
    tb = 0.0;
    fVar1 = tb;
    fVar2 = tg;
    fVar3 = tr;
  }
  tr = fVar3;
  tg = fVar2;
  tb = fVar1;
  *r = tr;
  *g = tg;
  *b = tb;
  return;
}