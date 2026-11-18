int clip(double *px, double *py, double *pz,
        double xmin, double xmax, double ymin, double ymax, double zmin, double zmax) {

    int iClip = 0;




    if (*px < xmin) {
        *px = xmin;
        iClip = 1;
    } else if (*px > xmax) {
        *px = xmax;
        iClip = 1;
    }
    if (*py < ymin) {
        *py = ymin;
        iClip = 1;
    } else if (*py > ymax) {
        *py = ymax;
        iClip = 1;
    }
    if (*pz < zmin) {
        *pz = zmin;
        iClip = 1;
    } else if (*pz > zmax) {

        *pz = zmax;
        iClip = 1;
    }

    return (iClip);

}