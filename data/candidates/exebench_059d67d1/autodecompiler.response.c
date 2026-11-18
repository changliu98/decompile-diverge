void sun_timeofday2time(long timeofday, long *hour, long *min, long *sec)
{
   *hour = timeofday / 3600;
   *min = (timeofday % 3600) / 60;
   *sec = timeofday % 60;
}