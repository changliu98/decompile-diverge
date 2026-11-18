void rsQuat_preMult(float *q,float *postQuat)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float tempw;
  float tempz;
  float tempy;
  float tempx;
  float *postQuat_local;
  float *q_local;
  
  fVar1 = *q;
  fVar2 = q[1];
  fVar3 = q[2];
  fVar4 = q[3];
  *q = -postQuat[1] * fVar3 + fVar2 * postQuat[2] + fVar4 * *postQuat + postQuat[3] * fVar1;
  q[1] = -postQuat[2] * fVar1 + fVar3 * *postQuat + fVar4 * postQuat[1] + postQuat[3] * fVar2;
  q[2] = -*postQuat * fVar2 + fVar1 * postQuat[1] + fVar4 * postQuat[2] + postQuat[3] * fVar3;
  q[3] = -fVar3 * postQuat[2] + -fVar2 * postQuat[1] + fVar4 * postQuat[3] + -(fVar1 * *postQuat);
  return;
}