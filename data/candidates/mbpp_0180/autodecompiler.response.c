double func0(double latA, double lngA, double latB, double lngB) {
    double arcLatA = latA * 3.141592653589793238462643/180;
    double arcLatB = latB * 3.141592653589793238462643/180;
    double x = cos(arcLatA) * cos(arcLatB) * cos(lngA - lngB);
    double y = sin(arcLatA) * sin(arcLatB);
    double s = x + y;
    if (s > 1) {
        s = 1;
    }
    if (s < -1) {
        s = -1;
    }
    double alpha = acos(s);
    return alpha * 6378137.0;
}