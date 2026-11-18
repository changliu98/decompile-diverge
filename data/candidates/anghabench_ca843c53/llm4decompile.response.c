char maya_pb_route_shift(int idx)
{
  char *route_shift = "\b\x14";
  return route_shift[idx % 10];
}