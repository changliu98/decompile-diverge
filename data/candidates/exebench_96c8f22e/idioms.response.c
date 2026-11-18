void pa(float *e, float dt, float r)
{
  long i;
  for (i = 0; i < 6; i++) {
    e[0] = e[0] + e[1] + e[2] - e[3];
    e[1] = e[0] + e[1] - e[2] + e[3];
    e[2] = e[0] - e[1] + e[2] + e[3];
    e[3] = e[0] + e[1] + e[2] + e[3];
    e[0] = e[0] * dt;
    e[1] = e[1] * dt;
    e[2] = e[2] * dt;
    e[3] = e[3] * dt / r;
  }
}