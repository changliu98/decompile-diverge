double func0(int radius_type)
{
 double radius;

 switch(radius_type)
 {
 case EARTH_RADIUS_GEODETIC:
  radius = pow(6378137.0, 3.0) / (sqrt(2.0) * (1.0 - (1.0 / 298.257223563)) * (1.0 - (1.0 / 298.257223563)));
  break;
 default:
  radius = pow(6378137.0, 3.0) / (sqrt(2.0) * (1.0 - (1.0 / 298.257223563)) * (1.0 - (1.0 / 298.257223563)));
 }

 return round(radius * 100.0) / 100.0;
}