void freduce_degree(limb *output)

{
  limb *output_local;
  
  output[8] = output[0x12] * 0x10 + output[8];
  output[8] = output[0x12] * 2 + output[8];
  output[8] = output[0x12] + output[8];
  output[7] = output[0x11] * 0x10 + output[7];
  output[7] = output[0x11] * 2 + output[7];
  output[7] = output[0x11] + output[7];
  output[6] = output[0x10] * 0x10 + output[6];
  output[6] = output[0x10] * 2 + output[6];
  output[6] = output[0x10] + output[6];
  output[5] = output[0xf] * 0x10 + output[5];
  output[5] = output[0xf] * 2 + output[5];
  output[5] = output[0xf] + output[5];
  output[4] = output[0xe] * 0x10 + output[4];
  output[4] = output[0xe] * 2 + output[4];
  output[4] = output[0xe] + output[4];
  output[3] = output[0xd] * 0x10 + output[3];
  output[3] = output[0xd] * 2 + output[3];
  output[3] = output[0xd] + output[3];
  output[2] = output[0xc] * 0x10 + output[2];
  output[2] = output[0xc] * 2 + output[2];
  output[2] = output[0xc] + output[2];
  output[1] = output[0xb] * 0x10 + output[1];
  output[1] = output[0xb] * 2 + output[1];
  output[1] = output[0xb] + output[1];
  *output = output[10] * 0x10 + *output;
  *output = output[10] * 2 + *output;
  *output = output[10] + *output;
  return;
}