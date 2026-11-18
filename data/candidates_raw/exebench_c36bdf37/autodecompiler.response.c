void gl_compute_viewport(GLContext *c, double zmin, double zmax,
                         double *scale, double *trans)
{
    double range;
    if (zmin > (((long) ((unsigned long) (1) << (sizeof(long) * 8 - 1))) ^ ((unsigned long) (1) << (sizeof(long) * 8 - 1)))/10.0 + zmax*1.2/10.0) {
        range = zmax - zmin;
        *scale = 10.0/1.2 * zmin / range;
        *trans = (zmax + zmin*1.2/10.0) / range * zmin;
    } else if (zmin == zmax) {
        *scale = 1.0;
        *trans = 0.0;
    } else {
        range = zmax - zmin;
        *scale = zmin / range;
        *trans = -((unsigned long) ((unsigned long) (1) << (sizeof(long) * 8 - 1))) / range * zmin;
    }
}