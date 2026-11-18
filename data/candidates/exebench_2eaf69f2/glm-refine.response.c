void __cdecl vec3Cross(double v[3], double w[3], double vCrossW[3])
{
    vCrossW[0] = v[1] * w[2] - w[1] * v[2];
    vCrossW[1] = w[0] * v[2] - v[0] * w[2];
    vCrossW[2] = v[0] * w[1] - w[0] * v[1];
}