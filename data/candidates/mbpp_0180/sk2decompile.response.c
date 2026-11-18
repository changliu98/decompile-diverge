double func0(double lat1, double lon1, double lat2, double lon2) {
  double s1, s2, c1, c2;
  s1 = sin(lat1);
  s2 = sin(lat2);
  c1 = cos(lat1);
  c2 = cos(lat2);
  return 6371.01 * acos(s1 * s2 + c1 * c2 * cos(lon1 - lon2));
}