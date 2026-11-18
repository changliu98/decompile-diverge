void goertzel_filter_v1(short *delay,short input,short coefficient)

{
  short sVar1;
  short product;
  short coefficient_local;
  short input_local;
  short *delay_local;
  
  sVar1 = delay[2];
  delay[2] = delay[1];
  delay[1] = (input >> 7) + ((short)((long)delay[1] * (long)coefficient >> 0xe) - sVar1);
  return;
}