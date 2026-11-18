int obdRevConvert_34_3B(float value, uint8_t *A, uint8_t *B, uint8_t *C, uint8_t *D)
{
  uint32_t val = (uint32_t)(value / 0.01);
  *A = val / 256;
  *B = val % 256;
  return 2;
}