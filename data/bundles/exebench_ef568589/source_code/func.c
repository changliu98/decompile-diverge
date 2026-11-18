#include <stdio.h>

#include <stdlib.h>

#include <stdarg.h>

#include <math.h>

#include <string.h>

void mat3f_rotateQuatVec_new(float matrix[9], const float quat[4])
{
 int X=0, Y=1, Z=2, W=3;
 float s = 2.0 / (quat[X]*quat[X] + quat[Y]*quat[Y] +
                  quat[Z]*quat[Z] + quat[W]*quat[W]);
 float xs, ys, zs,
       wx, wy, wz,
       xx, xy, xz,
       yy, yz, zz;

 xs = quat[X] * s; ys = quat[Y] * s; zs = quat[Z] * s;
 wx = quat[W] * xs; wy = quat[W] * ys; wz = quat[W] * zs;
 xx = quat[X] * xs; xy = quat[X] * ys; xz = quat[X] * zs;
 yy = quat[Y] * ys; yz = quat[Y] * zs; zz = quat[Z] * zs;


 matrix[0] = 1.0 - (yy + zz);
 matrix[3] = xy - wz;
 matrix[6] = xz + wy;


 matrix[1] = xy + wz;
 matrix[4] = 1.0 - (xx + zz);
 matrix[7] = yz - wx;


 matrix[2] = xz - wy;
 matrix[5] = yz + wx;
 matrix[8] = 1.0 - (xx + yy);
}
