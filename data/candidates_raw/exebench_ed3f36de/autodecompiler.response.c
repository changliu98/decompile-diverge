void xy_mean(double *mean, double *xy, int npts)
{
    double xsum, ysum;
    int i;

    xsum = 0.0;
    ysum = 0.0;

    for (i = 0; i < npts*2; i += 2) {
        xsum += xy[i];
    }

    for (i = 0; i < npts*2; i += 2) {
        ysum += xy[i+1];
    }

    mean[0] = xsum / (double) npts;
    mean[1] = ysum / (double) npts;
}