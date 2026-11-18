void __cdecl freduce_degree(limb *output)
{
  output[8] += 16 * output[18];
  output[8] += 2 * output[18];
  output[8] += output[18];
  output[7] += 16 * output[17];
  output[7] += 2 * output[17];
  output[7] += output[17];
  output[6] += 16 * output[16];
  output[6] += 2 * output[16];
  output[6] += output[16];
  output[5] += 16 * output[15];
  output[5] += 2 * output[15];
  output[5] += output[15];
  output[4] += 16 * output[14];
  output[4] += 2 * output[14];
  output[4] += output[14];
  output[3] += 16 * output[13];
  output[3] += 2 * output[13];
  output[3] += output[13];
  output[2] += 16 * output[12];
  output[2] += 2 * output[12];
  output[2] += output[12];
  output[1] += 16 * output[11];
  output[1] += 2 * output[11];
  output[1] += output[11];
  *output += 16 * output[10];
  *output += 2 * output[10];
  *output += output[10];
}