void reduce_grid_address(int *address,int *mesh)

{
  int i;
  int *mesh_local;
  int *address_local;
  
  for (i = 0; i < 3; i = i + 1) {
    address[i] = address[i] - mesh[i] * (uint)(mesh[i] / 2 < address[i]);
  }
  return;
}