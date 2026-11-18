void ecRotate(double v[3], double sin_theta, double cos_theta) {
  double tmp;
  tmp = v[1] * cos_theta + v[2] * sin_theta;
  v[2] = v[2] * cos_theta - v[1] * sin_theta;
  v[1] = tmp;
}