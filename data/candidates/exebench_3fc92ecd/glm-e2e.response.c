void julian_to_date(long julian, int *year, int *month, int *day) {
    long a = julian + 68569;
    long b = (4 * a) / 146097;
    a = a - ((b * 146097 + 3) / 4);
    long c = ((a + 1) * 4000) / 1461001;
    a = a - ((c * 1461) / 4) + 31;
    long d = (80 * a) / 2447;
    *day = (int)(a - (d * 2447) / 80);
    long e = d / 11;
    *month = (int)(d + 2 - e * 12);
    *year = (int)((b - 49) * 100 + c + e);
}