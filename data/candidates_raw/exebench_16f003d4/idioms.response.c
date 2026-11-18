void euler(double *u, double *v, double *u1, double dt)
{
  int i; int j;
  for (j = 0; j < 19; j = j + 6)
    for (i = 0; i < 3; i++)
      v[(i + j) + 3] = (2 * (u[(i + j)] - v[(i + j)]) / (2 * dt)
        + 2 * (u[(i + j) + 1] - v[(i + j) + 1]) / (2 * dt)) / (dt);
}