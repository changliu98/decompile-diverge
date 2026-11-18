static inline int epindex_to_epnum(int epindex, int *epdir)
{
 int dir_in = epindex % 2;

 if (epdir)
  *epdir = dir_in;







 return (epindex + dir_in) / 2;
}