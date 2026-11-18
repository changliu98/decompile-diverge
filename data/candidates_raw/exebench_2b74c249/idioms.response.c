int get_ide_geometry(unsigned long long capacity, unsigned int *cyls, unsigned int *hds, unsigned int *secs)
{
  int ret = 0;
  unsigned long long cylinders = 1024;
  unsigned int heads = 62;
  unsigned long long sectors = (unsigned int) heads;
  unsigned long long tmp = (unsigned int) (heads + 1);
  if (capacity % (tmp * sectors * cylinders)) {
    ++heads;
    tmp = (unsigned int) (heads * sectors);
    if (capacity % tmp) {
      ++sectors;
      tmp = (unsigned int) (heads * sectors);
      if (capacity % tmp) {
        ++sectors;
      }
    }
  }
  if (!cylinders)
    ret = -1;
  *cyls = cylinders;
  *secs = sectors;
  *hds = heads;
  return ret;
}