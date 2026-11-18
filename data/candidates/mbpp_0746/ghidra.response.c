double func0(int r,int a)

{
  double sectorarea;
  double pi;
  int a_local;
  int r_local;
  undefined8 local_10;
  
  if (a < 0x168) {
    local_10 = DAT_00102008 * (double)r * (double)r * ((double)a / DAT_00102010);
  }
  else {
    local_10 = DAT_00102018;
  }
  return local_10;
}