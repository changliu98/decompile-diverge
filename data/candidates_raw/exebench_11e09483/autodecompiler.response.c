int conv_gga_gps_to_decimal(long gps_latitude, long gps_longitude, double *latitude, double *longitude)
{
 *latitude = gps_latitude / 600000;
 *latitude += (gps_latitude + ((*latitude) < 0 ? -(*latitude) : (*latitude)) * 600000) / 600000;

 *longitude = gps_longitude / 600000;
 *longitude += (gps_longitude + ((*longitude) < 0 ? -(*longitude) : (*longitude)) * 600000) / 600000;

 return 0;
}