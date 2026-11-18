int pos2ddd(long latitude,long longitude,double *lat_dd,double *long_ddd)

{
  double *long_ddd_local;
  double *lat_dd_local;
  long longitude_local;
  long latitude_local;
  
  *lat_dd = (double)(int)(latitude / 600000);
  *lat_dd = (-*lat_dd * DAT_00102008 + (double)latitude) / DAT_00102008 + *lat_dd;
  *long_ddd = (double)(int)(longitude / 600000);
  *long_ddd = (-*long_ddd * DAT_00102008 + (double)longitude) / DAT_00102008 + *long_ddd;
  return 0;
}