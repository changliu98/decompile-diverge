void breakup(short fcs_bit[13], unsigned short val)
{
  int i;
  for (i = 0; i < 13; i++)
    fcs_bit[i] = 0;

  if (val >= 4096)
    {
      fcs_bit[12] = 1;
      val -= 4096;
    }
  if (val >= 2048)
    {
      fcs_bit[11] = 1;
      val -= 2048;
    }
  if (val >= 1024)
    {
      fcs_bit[10] = 1;
      val -= 1024;
    }
  if (val >= 512)
    {
      fcs_bit[9] = 1;
      val -= 512;
    }
  if (val >= 256)
    {
      fcs_bit[8] = 1;
      val -= 256;
    }
  if (val >= 128)
    {
      fcs_bit[7] = 1;
      val -= 128;
    }
  if (val >= 64)
    {
      fcs_bit[6] = 1;
      val -= 64;
    }
  if (val >= 32)
    {
      fcs_bit[5] = 1;
      val -= 32;
    }
  if (val >= 16)
    {
      fcs_bit[4] = 1;
      val -= 16;
    }
  if (val >= 8)
    {
      fcs_bit[3] = 1;
      val -= 8;
    }
  if (val >= 4)
    {
      fcs_bit[2] = 1;
      val -= 4;
    }
  if (val >= 2)
    {
      fcs_bit[1] = 1;
      val -= 2;
    }
  if (val == 1)
    fcs_bit[0] = 1;
}