void conv_sign(uint sign_bit,int *value)

{
  int *value_local;
  uint sign_bit_local;
  
  if ((*value & sign_bit) != 0) {
    *value = sign_bit * 2 - *value;
    *value = -*value;
  }
  return;
}