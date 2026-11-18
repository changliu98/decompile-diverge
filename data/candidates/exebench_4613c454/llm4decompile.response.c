void cquat_scale(double *qdest, const double *qorg, double c)
{
  qdest[0] = qorg[0] * c;
  qdest[1] = qorg[1] * c;
  qdest[2] = qorg[2] * c;
  qdest[3] = qorg[3] * c;
}