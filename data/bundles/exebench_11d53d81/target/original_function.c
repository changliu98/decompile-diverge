void eeval(double X, double A, double B, double C, double D,
            double *pQ, double *pdQ, double *pB1, double *pC2) {
    double q0, B1, C2, dQ, Q;
    q0 = A*X; B1 = q0 + B; C2 = B1*X + C;
    dQ = (q0 + B1)*X + C2; Q = C2*X + D;
    *pQ = Q; *pdQ = dQ; *pB1 = B1; *pC2 = C2;
}