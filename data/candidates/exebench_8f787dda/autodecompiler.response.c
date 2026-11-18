void index_to_xwy(int index, int nlon, int *x, int *y) {
  *x = index%nlon;
  *y = index/nlon;
}