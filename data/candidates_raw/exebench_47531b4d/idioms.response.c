void normalizeQuaternion(float *q)
{
  int i;
  float mag = q[0]*q[0]+q[1]*q[1]+q[2]*q[2]+q[3]*q[3];
  for(i=0;i<4;i++)
    q[i]=q[i]/mag;
}