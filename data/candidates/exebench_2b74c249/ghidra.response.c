int setsize(unsigned_long capacity,uint *cyls,uint *hds,uint *secs)

{
  unsigned_long temp;
  unsigned_long cylinders;
  unsigned_long sectors;
  unsigned_long heads;
  uint rv;
  uint *secs_local;
  uint *hds_local;
  uint *cyls_local;
  unsigned_long capacity_local;
  
  rv = 0;
  cylinders = 0x400;
  sectors._0_4_ = 0x3e;
  heads = capacity / 0xf800;
  if (capacity % 0xf800 != 0) {
    heads = heads + 1;
    sectors = capacity / (heads * 0x400);
    if (capacity % (heads * 0x400) != 0) {
      sectors = sectors + 1;
      cylinders = capacity / (heads * sectors);
    }
  }
  if (cylinders == 0) {
    rv = 0xffffffff;
  }
  *cyls = (uint)cylinders;
  *secs = (uint)sectors;
  *hds = (uint)heads;
  return rv;
}