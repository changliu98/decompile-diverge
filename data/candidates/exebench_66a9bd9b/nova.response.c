void fft4pt(float m[3][3]) {
    float mt[3][3];
    float det;
    float a, b, c, d, e, f, g, h, i;

    a = m[0][0];
    b = m[0][1];
    c = m[0][2];
    d = m[1][0];
    e = m[1][1];
    f = m[1][2];
    g = m[2][0];
    h = m[2][1];
    i = m[2][2];

    mt[0][0] = e * i - f * h;
    mt[0][1] = c * h - b * i;
    mt[0][2] = b * f - c * e;
    mt[1][0] = d * f - g * e;
    mt[1][1] = a * i - c * g;
    mt[1][2] = c * g - d * f;
    mt[2][0] = d * h - g * b;
    mt[2][1] = b * g - a * h;
    mt[2][2] = a * e - b * d;

    det = a * mt[0][0] + d * mt[1][0] + g * mt[2][0];

    m[0][0] = mt[0][0] / det;
    m[0][1] = mt[0][1] / det;
    m[0][2] = mt[0][2] / det;
    m[1][0] = mt[1][0] / det;
    m[1][1] = mt[1][1] / det;
    m[1][2] = mt[1][2] / det;
    m[2][0] = mt[2][0] / det;
    m[2][1] = mt[2][1] / det;
    m[2][2] = mt[2][2] / det;
}