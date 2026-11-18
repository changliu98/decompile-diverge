int get_ep_index(int epindex, int *epdir)
{
  int dir = epindex % 2;
  if (epdir)
    *epdir = dir;
  return (epindex + dir) / 2;
}