void func0(double jd, int *hour, int *min, float *sec) {
    double tm, secs;
    int mins;

    tm = jd + 0.5;
    if (tm < 0.0)
        tm += 360.0;
    tm /= 360.0;
    secs = tm * SECSPERDAY;
    mins = secs / SECSPERMIN;
    *hour = mins / MINS_PER_HOUR;
    secs -= mins * SECSPERMIN;
    *min = mins - *hour * MINS_PER_HOUR;
    secs *= SECSPERMIN;
    *sec = (float)secs;
}