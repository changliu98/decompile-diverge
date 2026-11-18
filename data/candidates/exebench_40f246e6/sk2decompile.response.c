float interp_tri(float *v, float x, float y, int dir) {
  double x1, y1, v0, v1, v3, v2, v01, v13, r;
  if (x < 0.00001)
    x1 = 0.0;
  else if (x > 0.99999)
    x1 = 1.0;
  else
    x1 = x;
  if (y < 0.00001)
    y1 = 0.0;
  else if (y > 0.99999)
    y1 = 1.0;
  else
    y1 = y;
  if (x1 == 0.0) {
    if (y1 == 0.0)
      return v[0];
    else if (y1 == 1.0)
      return v[2];
  } else if (x1 == 1.0) {
    if (y1 == 0.0)
      return v[1];
    else if (y1 == 1.0)
      return v[3];
  }
  if (dir > 0) {
    v0 = v[0];
    v1 = v[1];
    v3 = v[3];
    v2 = v[2];
  } else {
    x1 = 1.0 - x1;
    v0 = v[1];
    v1 = v[0];
    v3 = v[2];
    v2 = v[3];
  }
  if (x1 >= y1) {
    v01 = v0;
    v13 = v1;
  } else {
    v01 = v1;
    v13 = v3;
    x1 = 1.0 - x1;
    y1 = 1.0 - y1;
  }
  r = v01 + (v13 - v01) * x1;
  r += (v13 - v01) * (y1 / x1);
  return r;
}