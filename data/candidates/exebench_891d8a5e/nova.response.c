void decdms(double jd, int *hour, int *min, float *sec) {
    double t = jd;
    int h, m;
    t = t - (int)t;
    t = t * 24;
    h = (int)t;
    *hour = h;
    t = t - h;
    t = t * 60;
    m = (int)t;
    *min = m;
    t = t - m;
    t = t * 60;
    *sec = (float)t;
}