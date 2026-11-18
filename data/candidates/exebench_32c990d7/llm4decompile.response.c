void conv_sign(uint32_t sign_bit, uint32_t *value)
{
 if (*value & sign_bit) {
  *value = sign_bit*2 - *value;
  *value = 0 - *value;
 }
}