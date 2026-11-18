float func0(float x, struct Complex *y) {
    float d;
    d = (y->re * y->re) + (y->im * y->im);
    y->im = (y->re * y->im * (-1)) + (x * y->re);
    y->re = d;
    return (d);
}