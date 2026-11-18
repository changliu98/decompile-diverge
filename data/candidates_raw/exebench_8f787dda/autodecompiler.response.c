void xyz2latlon(int index, int nlon, int *x, int *y) {
  *x = index%nlon;
  *y = index/nlon;
}