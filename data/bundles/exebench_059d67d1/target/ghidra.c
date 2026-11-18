void sun_timeofday2time(long timeofday,int *hour,int *min,int *sec)

{
  int *sec_local;
  int *min_local;
  int *hour_local;
  long timeofday_local;
  
  *hour = (int)(timeofday / 0xe10);
  *min = (int)((timeofday % 0xe10) / 0x3c);
  *sec = (int)(timeofday % 0x3c);
  return;
}