void point_computing(double wh[4], double wh2[4], double wh3[4], double *p1,
                     double *p2) {
    double sum = wh[0] + wh[1] + wh[2] + wh[3];
    *p1 = (wh[0] * wh2[0] + wh[1] * wh2[1] + wh[2] * wh2[2] + wh[3] * wh2[3]) / sum;
    *p2 = (wh[0] * wh3[0] + wh[1] * wh3[1] + wh[2] * wh3[2] + wh[3] * wh3[3]) / sum;
}