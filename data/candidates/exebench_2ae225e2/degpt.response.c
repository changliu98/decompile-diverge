void make_double_bigendian(double *x)

{
  double dVar1;
  anon_union_8_2_94730023 v;
  anon_union_8_2_94730023 u;
  double *x_local;
  
  dVar1 = *x;
  u.b[7] = (uchar)((ulong)dVar1 >> 0x38);
  u.b[6] = (uchar)((ulong)dVar1 >> 0x30);
  u.b[5] = (uchar)((ulong)dVar1 >> 0x28);
  u.b[4] = (uchar)((ulong)dVar1 >> 0x20);
  u.b[3] = (uchar)((ulong)dVar1 >> 0x18);
  u.b[2] = (uchar)((ulong)dVar1 >> 0x10);
  u.b[1] = (uchar)((ulong)dVar1 >> 8);
  u.b[0] = SUB81(dVar1,0);
  *x = (double)CONCAT17(u.b[0],CONCAT16(u.b[1],CONCAT15(u.b[2],CONCAT14(u.b[3],CONCAT13(u.b[4],
                                                  CONCAT12(u.b[5],CONCAT11(u.b[6],u.b[7])))))));
  return;
}