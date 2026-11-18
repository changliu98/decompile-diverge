void reduce_grid_address(long *address,long *mesh)

{
  long i;
  long *mesh_local;
  long *address_local;
  
  for (i = 0; i < 3; i = i + 1) {
    address[i] = address[i] - mesh[i] * (long)(int)(uint)(mesh[i] / 2 < address[i]);
  }
  return;
}