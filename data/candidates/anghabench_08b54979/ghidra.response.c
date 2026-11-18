uint32_t F(uint32_t x,uint32_t y,uint32_t z)

{
  uint32_t z_local;
  uint32_t y_local;
  uint32_t x_local;
  
  return x & y | (x ^ 0xffffffff) & z;
}