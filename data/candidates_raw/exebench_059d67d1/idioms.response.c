void get_timeofday(long timeofday, int *hour, int *min, int *sec)
{
  *hour = (int)(timeofday / 3600);
  *min = (int)(timeofday % 3600 / 60);
  *sec = (int)(timeofday % 60);
  return;
}