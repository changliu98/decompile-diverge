uint and_peep2_q(uint y,uint *x)

{
  uint *x_local;
  uint y_local;
  
  *x = y & 0xfe;
  return y;
}