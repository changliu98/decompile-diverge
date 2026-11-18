void reduce_grid_address_double(int *address,int *mesh)

{
  int i;
  int *mesh_local;
  int *address_local;
  
  for (i = 0; i < 3; i = i + 1) {
    address[i] = address[i] - mesh[i] * 2 * (uint)(mesh[i] < address[i]);
  }
  return;
}