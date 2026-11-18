double func0(double lat1, double long1, double lat2, double long2)
{
    double a; double b; double c; double d; double e;
    a = sin(lat1);
    b = sin(lat2);
    c = cos(lat1);
    d = cos(lat2);
    e = c * d * cos(long1 - long2);
    return (6371.01 * acos(a * b + e));
}