void rmHSVtoRGB(float H, float S, float V, float *R, float *G, float *B) {
  float r, g, b, f, p, q;
  int i;
  r = V;
  g = 0;
  b = 0;
  if (V == 0) {
    r = g = b = 0;
  } else if (S == 0) {
    r = g = b = V;
  } else {
    f = H * 6;
    if (f >= 6) f = 0;
    i = (int)f;
    p = V * (1 - S);
    q = V * (1 - S * (f - i));
    if (i == 0) {
      r = V;
      g = q;
      b = p;
    } else if (i == 1) {
      r = q;
      g = V;
      b = p;
    } else if (i == 2) {
      r = p;
      g = V;
      b = q;
    } else if (i == 3) {
      r = p;
      g = q;
      b = V;
    } else if (i == 4) {
      r = q;
      g = p;
      b = V;
    } else if (i == 5) {
      r = V;
      g = p;
      b = q;
    }
  }
  *R = r;
  *G = g;
  *B = b;
}