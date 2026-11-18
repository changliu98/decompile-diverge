int dms2dd(long dms_lat, long dms_long, double *dd_lat, double *dd_long)
{
  *dd_lat = dms_lat / 10000000;
  *dd_lat += dms_lat % 10000000 / 600000.0;
  *dd_long = dms_long / 10000000;
  *dd_long += dms_long % 10000000 / 600000.0;
  return 0;
}