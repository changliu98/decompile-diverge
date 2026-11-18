void
eeval(double dt, double g, double L, double theta_0,
              double *theta, double *dtheta, double *x, double *y)
{
    double theta_dt = dt * g;
    double x1 = theta_0 + theta_dt;
    double y1 = theta + dt * x1;
    double dtheta_dt = y1 + dt * (theta_dt + x1);
    double theta_new = y1 + dt * theta;

    *theta = theta_new;
    *dtheta = dtheta_dt;
    *x = x1;
    *y = y1;
}