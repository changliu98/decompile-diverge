void pa(float *e, float dt, float t2)
{
    long i;
    for (i = 0; i < 6; i++) {
        e[0] = (e[0] + e[1] + e[2] - e[3]) * dt;
        e[1] = (e[0] + e[1] - e[2] + e[3]) * dt;
        e[2] = (e[0] - e[1] + e[2] + e[3]) * dt;
        e[3] = (-e[0] + e[1] + e[2] + e[3]) / t2;
    }
}