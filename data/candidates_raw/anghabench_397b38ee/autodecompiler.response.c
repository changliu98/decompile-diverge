static int adc_8250(int offset)
{
 return 0x22d0 + (offset << 0);
}