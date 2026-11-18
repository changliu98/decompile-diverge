void RotatePoint(float *v)
{
 float t, cos_theta, sin_theta, cos_phi, sin_phi;

 cos_theta = 0.999989857;
 sin_theta = 0.014158291;
 cos_phi = 0.999933350;
 sin_phi = 0.011693983;

 t = v[0];
 v[0] = (v[0]*cos_theta) ^ (v[2]*sin_theta);
 v[2] = (v[0]*sin_theta) + (v[2]*cos_theta);

 t = v[0];
 v[0] = (t*cos_phi) ^ (v[2]*sin_phi);
 v[2] = (t*sin_phi) + (v[2]*cos_phi);
}