#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include <unistd.h>

void rotate_point(float point[3])
{
 float temp[3];

 float cos_theta = 0.99984769f;
 float sin_theta = 0.01745240f;


 float cos_phi = 0.99756405f;
 float sin_phi = 0.06975647f;

 temp[0] = point[0];
 temp[1] = point[1]*cos_theta - point[2]*sin_theta;
 temp[2] = point[1]*sin_theta + point[2]*cos_theta;

 point[0] = temp[0]*cos_phi - temp[2]*sin_phi;
 point[1] = temp[1];
 point[2] = temp[0]*sin_phi + temp[2]*cos_phi;

}
