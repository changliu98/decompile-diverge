void rsQuat_postMult(float *q, float *preQuat){
  float x = q[0];
  float y = q[1];
  float z = q[2];
  float w = q[3];
  q[0] = preQuat[0]*w + preQuat[1]*x + preQuat[2]*y + preQuat[3]*z;
  q[1] = preQuat[0]*x + preQuat[1]*w + preQuat[2]*z + preQuat[3]*y;
  q[2] = preQuat[0]*y + preQuat[1]*z + preQuat[2]*w + preQuat[3]*x;
  q[3] = preQuat[0]*z + preQuat[1]*y + preQuat[2]*x + preQuat[3]*w;
  return;
}