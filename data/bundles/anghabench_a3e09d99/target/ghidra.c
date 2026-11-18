uint ring_size_to_bytes(uint ring_size)

{
  uint ring_size_local;
  
  return ring_size << 2;
}