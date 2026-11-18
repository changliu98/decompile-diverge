extern void quatmul(double r[4], double p[4], double q[4])
{

 r[0] = p[0]*q[0] - p[1]*q[1] - p[2]*q[2] - p[3]*q[3];
 r[1] = p[1]*q[0] + p[0]*q[1] + p[2]*q[3] - p[3]*q[2];
 r[2] = p[2]*q[0] + p[0]*q[2] + p[3]*q[1] - p[1]*q[3];
 r[3] = p[3]*q[0] + p[0]*q[3] + p[1]*q[2] - p[2]*q[1];
}