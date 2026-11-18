bool _is_valid_coord(int *coord, int *dims, int ndims) {
  int i;
  for (i = 0; i < ndims; i++) {
    if (coord[i] >= dims[i]) {
      return false;
    }
  }
  return true;
}