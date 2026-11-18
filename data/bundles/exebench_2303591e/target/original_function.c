void prod_vet(float *x, float *y, float *z){
 x[2] = y[0]*z[1] - z[0]*y[1];
 y[2] = z[0]*x[1] - x[0]*z[1];
 z[2] = x[0]*y[1] - y[0]*x[1];
}