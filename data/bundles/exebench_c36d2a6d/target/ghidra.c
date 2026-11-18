int epindex_to_epnum(int epindex,int *epdir)

{
  int dir_in;
  int *epdir_local;
  int epindex_local;
  
  if (epdir != (int *)0x0) {
    *epdir = epindex % 2;
  }
  return (epindex + epindex % 2) / 2;
}