double func0(double slat, double slon, double elat, double elon) {
  double dist = 6371.01 * acos(sin(slat) * sin(elat) +
                               cos(slat) * cos(elat) * cos(slon - elon));
  return dist;
}