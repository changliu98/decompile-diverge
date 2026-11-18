static int bbox(int nV, double *vertex, double *dv) {
    double bmin[3], bmax[3];
    int t, i, j, k1, k2, k3, k;

    for (j=0; j<3; j++) {
 bmin[j] = vertex[3*0+j];
 bmax[j] = vertex[3*0+j];
    }
    for (i=1; i<nV; i++) {
 for (j=0; j<3; j++) {
     if (bmin[j] > vertex[3*i+j]) bmin[j] = vertex[3*i+j];
     if (bmax[j] < vertex[3*i+j]) bmax[j] = vertex[3*i+j];
 }
    }
    for (t=0; t<3; t++) {
 dv[t] = (bmin[t] + bmax[t])/2.0;
    }
    for (t=0; t<3; t++) {
 dv[3+t] = 1.0;
 while ( dv[3+t] * (bmax[t] - bmin[t]) < 1.0) dv[3+t] *= 2.0;
 while ( dv[3+t] * (bmax[t] - bmin[t]) > 1.0) dv[3+t] /= 2.0;
    }
    k1 = 3, k2 = 4, k3 = 5;
    if (dv[k1]>dv[k2]) k=k1, k1=k2, k2=k;
    if (dv[k2]>dv[k3]) k=k2, k2=k3, k3=k;
    if (dv[k1]>dv[k2]) k=k1, k1=k2, k2=k;
    if (dv[k1]<dv[k2]) dv[k1] = dv[k2]/1.0;
    if (dv[k3]>dv[k2]) dv[k3] = dv[k2]*1.0;

    return 0;
}