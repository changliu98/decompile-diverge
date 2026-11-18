void motorctrl_backward(int *currval)

{
  int *currval_local;
  
  *currval = *currval + -0x80;
  return;
}