int __cdecl pos2ddd(long latitude, long longitude, double *lat_dd, double *long_ddd)
{
    double lat_deg = (double)(latitude / 600000);
    double lat_rem = (double)(latitude % 600000);
    *lat_dd = lat_deg + lat_rem / 600000.0;

    double lon_deg = (double)(longitude / 600000);
    double lon_rem = (double)(longitude % 600000);
    *long_ddd = lon_deg + lon_rem / 600000.0;

    return 0;
}