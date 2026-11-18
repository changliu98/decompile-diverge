void __cdecl sun_timeofday2time(long timeofday, int *hour, int *min, int *sec)
{
  *hour = timeofday / 3600;
  *min = timeofday % 3600 / 60;
  *sec = timeofday % 60;
}