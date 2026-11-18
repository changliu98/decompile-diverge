void sun_timeofday2time(long total_seconds, int *out_hour, int *out_minute, int *out_second)
{
  // Calculate hours: divide total seconds by 3600 (0xe10 in hex)
  *out_hour = (int)(total_seconds / 0xe10);
  // Calculate minutes: get the remainder after dividing by 3600, then divide by 60 (0x3c in hex)
  *out_minute = (int)((total_seconds % 0xe10) / 0x3c);
  // Calculate seconds: get the remainder after dividing by 60 (0x3c in hex)
  *out_second = (int)(total_seconds % 0x3c);
}