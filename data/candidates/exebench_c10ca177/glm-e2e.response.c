void geom_matinv2d(double m[2][2]) {
    double det = 1.0 / (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
    double m00 = m[0][0];
    
    m[0][0] = det * m[1][1];
    m[0][1] = -det * m[0][1];
    m[1][0] = -det * m[1][0];
    m[1][1] = det * m00;
}