void shape(double x, double y, double N[4]) {
    N[0] = (1-x)*(1-y);
    N[1] = x*(1-y);
    N[2] = x*y;
    N[3] = (1-x)*y;
}