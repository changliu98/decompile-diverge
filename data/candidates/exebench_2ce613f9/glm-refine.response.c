void __cdecl add_ang_mom(double *L, float *c, float *pos)
{
    // Relative position vector (r)
    float rx = pos[0] - c[0];
    float ry = pos[1] - c[1];
    float rz = pos[2] - c[2];

    // Relative velocity/momentum vector (v)
    float vx = pos[3] - c[3];
    float vy = pos[4] - c[4];
    float vz = pos[5] - c[5];

    // L += r x v
    L[0] += (double)(ry * vz - rz * vy);
    L[1] += (double)(rz * vx - rx * vz);
    L[2] += (double)(rx * vy - ry * vx);
}