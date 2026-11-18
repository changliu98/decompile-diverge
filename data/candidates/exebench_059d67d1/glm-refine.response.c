void __cdecl sun_timeofday2time(long timeofday, int *hour, int *min, int *sec)
{
  // Extract hours from total seconds
  *hour = timeofday / 3600;
  
  // Extract remaining minutes
  *min = (timeofday % 3600) / 60;
  
  // Extract remaining seconds
  *sec = timeofday % 60;
}