int jrand_(int *n,int *ix,int *iy,int *iz)
{

  int ret_val;


  *ix = (3141 * *ix + 1) % 30082;
  *iy = (3142 * *iy + 1) % 30323;
  *iz = (3140 * *iz + 1) % 30353;
  jrand_::x = (double) *ix / 30082.0 + (double) *iy / 30323.0 + (double) *iz /
    30353.0;
  jrand_::u = jrand_::x - (int) jrand_::x;
  ret_val = (int) (*n * jrand_::u + 1.0);
  return ret_val;
}