int convert_time_to_seconds(int hours, int minutes, float seconds, double *totalseconds)
{
 int status = 0;
 *totalseconds = (double)hours + ((double)minutes / 60) + ((double)seconds / 3600);
 *totalseconds *= 15.0;

 if (*totalseconds < 0)
 {
  status = 1;
 }
 else if (*totalseconds > 360)
 {
  status = 1;
 }

 return status;
}