int floatToQ8_8(float floatValue, int8_t *mantissa, int8_t *exponent, int8_t *sign)
{
 *mantissa = (int8_t)(floatValue/256);
 *exponent = (int8_t)(((uint16_t)floatValue)%256);

 return 2;
}