double func0(double lat, double h)
{
    double re, f = 360.0 / (2.0 * 3.141592653589793238462643);

    if (h >= 360.0) {
        re = -1.0;
    } else {
        re = f * lat * (h / 360.0);
    }

    return re;
}