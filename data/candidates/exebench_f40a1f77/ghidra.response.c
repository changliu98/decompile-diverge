/* WARNING: Restarted to delay deadcode elimination for space: stack */

void get_bits_exp(double x,double *a,int *n)

{
  uint uVar1;
  double dVar2;
  uint *v;
  uint *u;
  double t2;
  double t;
  int *n_local;
  double *a_local;
  double x_local;
  
  t2._4_4_ = (uint)((ulong)x >> 0x20);
  uVar1 = t2._4_4_ & 0x7ff00000;
  t2 = x;
                    /* WARNING: Ignoring partial resolution of indirect */
  t2._4_4_ = uVar1;
  if (((ulong)x & 0x7ff0000000000000) == 0) {
    dVar2 = DAT_00102018 * t2 * DAT_00102018 * DAT_00102018 * DAT_00102018 * DAT_00102018 *
            DAT_00102018;
    t2._4_4_ = (uint)((ulong)dVar2 >> 0x20);
    uVar1 = t2._4_4_ & 0x7ff00000;
    t2 = dVar2;
                    /* WARNING: Ignoring partial resolution of indirect */
    t2._4_4_ = uVar1;
                    /* WARNING: Ignoring partial resolution of indirect */
    t2._0_4_ = 0;
    *n = (uVar1 >> 0x14) - 0x43b;
    *a = x / (t2 / DAT_00102010);
  }
  else {
                    /* WARNING: Ignoring partial resolution of indirect */
    t2._0_4_ = 0;
    *n = (uVar1 >> 0x14) - 0x3ff;
    *a = x / t2;
  }
  return;
}