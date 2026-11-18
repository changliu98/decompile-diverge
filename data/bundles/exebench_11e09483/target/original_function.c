int pos2ddd( long latitude, long longitude, double *lat_dd, double *long_ddd )
{

    *lat_dd = (int) (latitude / 600000);
    *lat_dd += (double) (latitude - (*lat_dd * 600000)) / 600000.0;


    *long_ddd = (int) (longitude / 600000);
    *long_ddd += (double) (longitude - (*long_ddd * 600000)) / 600000.0;

    return 0;
}