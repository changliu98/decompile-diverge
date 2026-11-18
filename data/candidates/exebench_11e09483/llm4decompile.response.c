int pos2ddd(long latitude, long longitude, double *lat_dd, double *long_ddd)
{
    *lat_dd = (double)(latitude/600000);
    *lat_dd += ((double)latitude - (double)(latitude/600000)*600000)/600000;
    *long_ddd = (double)(longitude/600000);
    *long_ddd += ((double)longitude - (double)(longitude/600000)*600000)/600000;
    return 0;
}