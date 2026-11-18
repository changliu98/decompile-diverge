void sseround(float *vec)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *vec_local;
  
  fVar4 = (float)((uint)vec[1] & sseround::mask._4_4_);
  fVar5 = (float)((uint)vec[2] & sseround::mask._8_4_);
  fVar6 = (float)((uint)vec[3] & sseround::mask._12_4_);
  uVar1 = ~sseround::mask._4_4_;
  uVar2 = ~sseround::mask._8_4_;
  uVar3 = ~sseround::mask._12_4_;
  *vec = (float)((uint)(float)(int)(float)((uint)*vec & sseround::mask._0_4_) |
                ~sseround::mask._0_4_ & (uint)*vec);
  vec[1] = (float)((uint)(float)(int)fVar4 | uVar1 & (uint)vec[1]);
  vec[2] = (float)((uint)(float)(int)fVar5 | uVar2 & (uint)vec[2]);
  vec[3] = (float)((uint)(float)(int)fVar6 | uVar3 & (uint)vec[3]);
  return;
}