void get_grid_address(long *address,long *address_double,long *PS)

{
  int i;
  long *PS_local;
  long *address_double_local;
  long *address_local;
  
  for (i = 0; i < 3; i = i + 1) {
    address[i] = (address_double[i] - PS[i]) / 2;
  }
  return;
}