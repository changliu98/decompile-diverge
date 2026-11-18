void __cdecl cquat_scale(double *qdest, double c, const double *qorg)
{
  qdest[0] = c * qorg[0];
  qdest[1] = c * qorg[1];
  qdest[2] = c * qorg[2];
  qdest[3] = c * qorg[3];
}