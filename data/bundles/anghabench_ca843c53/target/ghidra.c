int maya_pb_route_shift(int idx)

{
  int idx_local;
  
  return (int)"\b\x14"[idx % 10];
}