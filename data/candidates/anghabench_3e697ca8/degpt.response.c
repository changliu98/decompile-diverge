uint swizzle(uint in,uint limit)

{
  uint out;
  uint limit_local;
  uint in_local;
  
  out = 0;
  in_local = in;
  for (limit_local = limit; limit_local != 0; limit_local = limit_local >> 1) {
    out = out << 1 | in_local & 1;
    in_local = in_local >> 1;
  }
  return out;
}