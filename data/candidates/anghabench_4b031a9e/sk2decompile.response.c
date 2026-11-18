static int valid_bo_pre_v2(unsigned long bo) {
  if ((bo & 0x14) == 0) return 1;
  if ((bo & 0x14) == 0x04) return !(bo & 0x02);
  if ((bo & 0x14) == 0x10) return !(bo & 0x08);
  if ((bo & 0x14) == 0x14) return 1;
  return 0;
}