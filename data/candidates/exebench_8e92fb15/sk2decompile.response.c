void cylinder(float r, float h, float *l, float *s, float *v) {
  *l = 2.0f * r * h * 22.0f / 7.0f;
  *s = 2.0f * r * (h + r) * 22.0f / 7.0f;
  *v = r * r * h * 22.0f / 7.0f;
}