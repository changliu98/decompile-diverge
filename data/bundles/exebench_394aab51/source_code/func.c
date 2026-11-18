
void rsQuat_postMult (float *q, float preQuat[4])
{
 float tempx = q[0];
 float tempy = q[1];
 float tempz = q[2];
 float tempw = q[3];

 q[0] = preQuat[3] * tempx + tempw * preQuat[0] + preQuat[1] * tempz - tempy * preQuat[2];
 q[1] = preQuat[3] * tempy + tempw * preQuat[1] + preQuat[2] * tempx - tempz * preQuat[0];
 q[2] = preQuat[3] * tempz + tempw * preQuat[2] + preQuat[0] * tempy - tempx * preQuat[1];
 q[3] = preQuat[3] * tempw - preQuat[0] * tempx - preQuat[1] * tempy - preQuat[2] * tempz;
}
