void sun_timeofday2time(long timeofday, int *hour, int *minute, int *second) {
  *hour = timeofday / 3600;
  timeofday -= *hour * 3600;
  *minute = timeofday / 60;
  timeofday -= *minute * 60;
  *second = timeofday;
}