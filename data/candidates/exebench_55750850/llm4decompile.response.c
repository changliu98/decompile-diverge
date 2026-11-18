void rotate_point(float *point)
{
 float phi = 0.52359877559829882;
 float cos_phi = 0.84804809615615488;
 float sin_phi = 0.52996399330952553;
 float theta = 0.31415926535897932;
 float cos_theta = 0.87758256189037273;
 float sin_theta = 0.47942553860420303;
 float temp[3];

 temp[0] = point[0] * cos_phi - point[1] * sin_phi * cos_theta - point[2] * sin_phi * sin_theta;
 temp[1] = point[0] * sin_phi + point[1] * cos_phi * cos_theta - point[2] * cos_phi * sin_theta;
 temp[2] = point[1] * sin_theta + point[2] * cos_theta;

 point[0] = temp[0];
 point[1] = temp[1];
 point[2] = temp[2];
}