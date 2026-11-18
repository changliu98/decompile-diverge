static void sun_mjulianday_to_date(int year, int *m, int *d, int *y) {
    int ndays, nleap;

    ndays = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 +
            (year - 1) / 400;
    nleap = (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    *y = ndays / (365 * 5 + 1);
    ndays -= (*y) * (365 * 5 + 1);
    *m = ndays / (30 * 5 + 1);
    ndays -= (*m) * (30 * 5 + 1);
    *d = ndays / 5 + 1;
}