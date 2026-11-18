void convert2ASCII(char input,char *output)

{
  byte bVar1;
  uchar temp;
  char *output_local;
  char input_local;
  
  bVar1 = input >> 4;
  if (bVar1 < 10) {
    *output = bVar1 + 0x30;
  }
  else {
    *output = bVar1 + 0x57;
  }
  bVar1 = input & 0xf;
  if (bVar1 < 10) {
    output[1] = bVar1 + 0x30;
  }
  else {
    output[1] = bVar1 + 0x57;
  }
  return;
}