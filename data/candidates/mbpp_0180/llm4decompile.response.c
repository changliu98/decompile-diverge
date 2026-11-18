double func0(double slat, double slon, double elat, double elon)
{
    double a;
    a = sin(slat)*sin(elat)+cos(slat)*cos(elat)*cos(slon-elon);
    return 6371.0*acos(a);
}