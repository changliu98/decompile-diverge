double __cdecl func0(double slat, double slon, double elat, double elon)
{
  double sin_slat = sin(slat);
  double sin_elat = sin(elat);
  double cos_slat = cos(slat);
  double cos_elat = cos(elat);
  double cos_delta_lon = cos(slon - elon);

  // Spherical law of cosines: d = R * acos(sin(φ1)sin(φ2) + cos(φ1)cos(φ2)cos(Δλ))
  // 6371.01 is the approximate radius of the Earth in kilometers.
  return 6371.01 * acos(sin_slat * sin_elat + cos_slat * cos_elat * cos_delta_lon);
}