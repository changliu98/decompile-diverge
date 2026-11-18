/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int jrand_(int *n,int *ix,int *iy,int *iz)

{
  int ret_val;
  int *iz_local;
  int *iy_local;
  int *ix_local;
  int *n_local;
  
  *ix = (*ix * 0xab) % 0x763d;
  *iy = (*iy * 0xac) % 0x7663;
  *iz = (*iz * 0xaa) % 0x7673;
  jrand_::x = (double)*ix / _DAT_00102020 + (double)*iy / DAT_00102018 + (double)*iz / DAT_00102010;
  jrand_::u = jrand_::x - (double)(int)jrand_::x;
  return (int)((double)*n * (jrand_::x - (double)(int)jrand_::x) + DAT_00102008);
}