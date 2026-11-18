int pos2ddd(long lat, long lon, double *latd, double *lond) {
  *latd = (double)(lat / 600000);
  *latd += (double)(lat - (long)(*latd) * 600000) / 600000.0;
  *lond = (double)(lon / 600000);
  *lond += (double)(lon - (long)(*lond) * 600000) / 600000.0;
  return 0;
}