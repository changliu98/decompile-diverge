
void rsQuat_preMult (float *q, float postQuat[4])
{



 float tempx = q[0];
 float tempy = q[1];
 float tempz = q[2];
 float tempw = q[3];

 q[0] = tempw * postQuat[0] + postQuat[3] * tempx + tempy * postQuat[2] - postQuat[1] * tempz;
 q[1] = tempw * postQuat[1] + postQuat[3] * tempy + tempz * postQuat[0] - postQuat[2] * tempx;
 q[2] = tempw * postQuat[2] + postQuat[3] * tempz + tempx * postQuat[1] - postQuat[0] * tempy;
 q[3] = tempw * postQuat[3] - tempx * postQuat[0] - tempy * postQuat[1] - tempz * postQuat[2];
}
