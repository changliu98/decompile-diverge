float lpcresampler(float xin, struct lpcresampler_t *self)
{
  int i;
  float y;
  self->lpcresampler_count++;
  if (self->lpcresampler_count <= self->lpcresampler_count_max)
    i = self->lpcresampler_count;
  else
  {
    i = self->lpcresampler_count_max;
    self->lpcresampler_count = self->lpcresampler_count_max;
  }
  self->lpcresampler_y[0] = (self->lpcresampler_y[i] * (1.0 - self->lpcresampler_alpha))
    + (self->lpcresampler_y[i - 1] * self->lpcresampler_alpha);
  y = self->lpcresampler_a[0] * self->lpcresampler_y[i]
    + self->lpcresampler_a[1] * self->lpcresampler_y[i - 1];
  y = y * self->lpcresampler_b[0] + self->lpcresampler_b[1];
  self->lpcresampler_y[i - 1] = self->lpcresampler_y[i];
  self->lpcresampler_y[i] = -self->lpcresampler_a[2] * self->lpcresampler_y[i - 2]
    + self->lpcresampler_a[3] * self->lpcresampler_y[i - 3] + y;
  self->lpcresampler_y[i - 2] = self->lpcresampler_y[i - 1];
  self->lpcresampler_y[i - 1] = self->lpcresampler_y[i];
  self->lpcresampler_y[i] = xin;
  return self->lpcresampler_y[0];
}