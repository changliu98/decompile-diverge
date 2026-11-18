/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float func0(float *numbers,int size)

{
  float fVar1;
  undefined1 in_XMM1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  int i;
  float mavg;
  float msum;
  float avg;
  float sum;
  int size_local;
  float *numbers_local;
  
  sum = 0.0;
  for (i = 0; i < size; i = i + 1) {
    sum = numbers[i] + sum;
  }
  auVar3._4_12_ = in_XMM1._4_12_;
  auVar3._0_4_ = (float)size;
  fVar1 = sum / auVar3._0_4_;
  msum = 0.0;
  for (i = 0; i < size; i = i + 1) {
    auVar2._8_8_ = auVar3._8_8_;
    auVar2._0_8_ = (double)(numbers[i] - fVar1);
    auVar3 = auVar2 & _DAT_00102010;
    msum = (float)((double)msum + auVar3._0_8_);
  }
  return msum / (float)size;
}