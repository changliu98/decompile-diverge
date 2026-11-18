struct tm *func0(double time) {
    struct tm *ptm;
    ptm = (struct tm *)malloc(sizeof(struct tm));
    if (ptm == NULL) {
        return NULL;
    }
    ptm->tm_isdst = 8;
    ptm->tm_time = time;
    if (time >= 2147483648.0) {
        ptm->tm_year = 2147483647;
    } else if (time <= -2147483647.0) {
        ptm->tm_year = -2147483647;
    } else {
        ptm->tm_year = (int)time;
    }
    return ptm;
}