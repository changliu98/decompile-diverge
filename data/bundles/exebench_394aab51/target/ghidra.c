void rsQuat_postMult(float *q,float *preQuat)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float tempw;
  float tempz;
  float tempy;
  float tempx;
  float *preQuat_local;
  float *q_local;
  
  fVar1 = *q;
  fVar2 = q[1];
  fVar3 = q[2];
  fVar4 = q[3];
  *q = -fVar2 * preQuat[2] + preQuat[1] * fVar3 + preQuat[3] * fVar1 + fVar4 * *preQuat;
  q[1] = -fVar3 * *preQuat + preQuat[2] * fVar1 + preQuat[3] * fVar2 + fVar4 * preQuat[1];
  q[2] = -fVar1 * preQuat[1] + *preQuat * fVar2 + preQuat[3] * fVar3 + fVar4 * preQuat[2];
  q[3] = -preQuat[2] * fVar3 + -preQuat[1] * fVar2 + preQuat[3] * fVar4 + -(*preQuat * fVar1);
  return;
}