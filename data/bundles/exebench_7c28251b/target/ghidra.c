void sun_gpstime2mjulianday(int week,double tow,long *daynum)

{
  long *daynum_local;
  double tow_local;
  int week_local;
  
  *daynum = (long)(week * 7) + (long)(tow / DAT_00102008) + 0xacd4;
  return;
}