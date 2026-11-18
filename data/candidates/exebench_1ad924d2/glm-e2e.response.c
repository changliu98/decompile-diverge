void pinvJ(double *out, double a, double b, double c, double d, double e) {
    double a2 = a * a;
    double b2 = b * b;
    double c2 = c * c;
    double d2 = d * d;
    double e2 = e * e;
    
    double c2_plus_d2 = c2 + d2;
    double ab = a * b;
    double de = d * e;
    double c_c2_d2_e2 = c * (c2_plus_d2 + e2);
    
    out[0] = -b * de + a * (c2 + e2);
    out[1] = b * c2_plus_d2 - a * de;
    out[2] = c_c2_d2_e2;
    out[3] = -c * (a * d + b * e);
    out[4] = d * (b2 + c2) - ab * e;
    out[5] = -ab * d + e * (a2 + c2);
    out[6] = out[3];
    out[7] = c * (a2 + b2 + c2);
    
    double det = out[0] * a + out[1] * b + out[2] * c;
    
    for (int i = 0; i < 8; i++) {
        out[i] /= det;
    }
}