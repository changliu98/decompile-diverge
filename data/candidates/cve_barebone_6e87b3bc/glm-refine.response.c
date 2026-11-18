void __cdecl quicktake_100_load_raw()
{
  unsigned char pixel[484][644];
  int row, col, rb;
  int pred, sharp, grad;
  unsigned char val;

  memset(pixel, 128, sizeof(pixel));
  getbithuff(-1, 0LL);

  // Phase 1: Decode Green Channel
  for (row = 2; row < (unsigned __int16)height + 2; ++row)
  {
    for (col = (row & 1) + 2; col < (unsigned __int16)width + 2; col += 2)
    {
      pred = (pixel[row - 1][col + 642] + 2 * pixel[row - 1][col + 1] + pixel[row - 1][col - 1]) >> 2;
      val = clamp_to_u8(quicktake_100_load_raw_gstep[getbithuff(4, 0LL)] + pred);
      pixel[row][col] = val;

      if (col < 4)
      {
        pixel[row + 1][(row & 1) == 0] = val;
        pixel[row - 1][col + 642] = val;
      }
      if (row == 2)
      {
        pixel[1][col + 3] = val;
        pixel[1][col + 1] = val;
      }
    }
    pixel[row][col] = val;
  }

  // Phase 2: Decode Red/Blue Channels
  for (rb = 0; rb < 2; ++rb)
  {
    for (row = rb + 2; row < (unsigned __int16)height + 2; row += 2)
    {
      for (col = 3 - (row & 1); col < (unsigned __int16)width + 2; col += 2)
      {
        if (row >= 4 && col >= 4)
        {
          grad = abs32(pixel[row - 1][col + 642] - pixel[row - 2][col - 2])
               + abs32(pixel[row - 2][col] - pixel[row - 2][col - 2])
               + abs32(pixel[row - 2][col] - pixel[row - 1][col + 642]);

          if (grad < 4)
            sharp = 0;
          else if (grad < 8)
            sharp = 1;
          else if (grad < 16)
            sharp = 2;
          else if (grad < 32)
            sharp = 3;
          else if (grad < 48)
            sharp = 4;
          else
            sharp = 5;
        }
        else
        {
          sharp = 2;
        }

        pred = (pixel[row - 1][col + 642] + pixel[row - 2][col]) >> 1;
        val = clamp_to_u8(quicktake_100_load_raw_rstep[4 * sharp + getbithuff(2, 0LL)] + pred);
        pixel[row][col] = val;

        if (row < 4)
          pixel[row - 2][col + 2] = val;
        if (col < 4)
          pixel[row + 1][col + 642] = val;
      }
    }
  }

  // Phase 3: Apply Low-Pass Filter / Smoothing
  for (row = 2; row < (unsigned __int16)height + 2; ++row)
  {
    for (col = 3 - (row & 1); col < (unsigned __int16)width + 2; col += 2)
    {
      pred = ((pixel[row][col + 1] + 4 * pixel[row][col] + pixel[row - 1][col + 643]) >> 1) - 256;
      pixel[row][col] = clamp_to_u8(pred);
    }
  }

  // Phase 4: Apply Tone Curve and Write to Output Image
  for (row = 0; row < (unsigned __int16)height; ++row)
  {
    for (col = 0; col < (unsigned __int16)width; ++col)
    {
      *((_WORD *)raw_image + col + (unsigned __int16)raw_width * row) = 
          quicktake_100_load_raw_t_curve[pixel[row + 2][col + 2]];
    }
  }

  maximum = 1023;
}