int __cdecl pos2ddd(long latitude, long longitude, double *lat_dd, double *long_ddd)
{
  *lat_dd = (double)(int)(latitude / 600000);
  *lat_dd = (COERCE_DOUBLE(*(_QWORD *)lat_dd ^ 0x8000000000000000LL) * 600000.0 + (double)(int)latitude) / 600000.0
          + *lat_dd;
  *long_ddd = (double)(int)(longitude / 600000);
  *long_ddd = (COERCE_DOUBLE(*(_QWORD *)long_ddd ^ 0x8000000000000000LL) * 600000.0 + (double)(int)longitude) / 600000.0
            + *long_ddd;
  return 0;
}