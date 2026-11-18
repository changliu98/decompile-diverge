void go_south_east(int *lat,int *lon)

{
  int *lon_local;
  int *lat_local;
  
  *lat = *lat + -1;
  *lon = *lon + 1;
  return;
}