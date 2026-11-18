void motorctrl_forward(int *currval)

{
  int *currval_local;
  
  *currval = *currval + 0x80;
  return;
}