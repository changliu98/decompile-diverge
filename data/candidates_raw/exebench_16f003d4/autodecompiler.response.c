void finish_lazy_updates_SOR(double *old, double *new, double *r,
        double tau)
{
    int i, j, k;
    for (i = 0; i < 19; i += 6)
        for (j = 0; j < 4; ++j)
        {
            k = i + j;
            double d = (r[k] - old[k]) / 2;
            double c = (r[k] + old[k]) / 2 - new[k];
            new[k + 3] = (c + 2 * d) / tau;
        }
}