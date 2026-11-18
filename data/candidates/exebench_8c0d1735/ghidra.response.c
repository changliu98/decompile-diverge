uint and_peep2_qi(uint y,uint *x)

{
  uint *x_local;
  uint y_local;
  
  *x = y & 0x5f;
  return y;
}