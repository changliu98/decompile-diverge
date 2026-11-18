int params_exactN(double *__restrict__ r, double *__restrict__ g,
                      double *__restrict__ rho, double *__restrict__ t,
                      double *__restrict__ p, double *__restrict__ e) {

    *r = 1.0;
    *g = 0.0;
    *rho = *g * 1.0e-6;
    *t = 1.0;
    *p = *r / (gamma * *t);
    *e = *p / (*rho * *rho);
    double tmp = *rho / *t;
    *g = tmp * tmp * 1.0e-6;
    *r = *g * gamma * *e;
    return 0;
}