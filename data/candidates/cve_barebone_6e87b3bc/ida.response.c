void __cdecl quicktake_100_load_raw()
{
  int v0; // eax
  int v1; // [rsp+8h] [rbp-4C1E8h]
  unsigned __int8 v2; // [rsp+Ch] [rbp-4C1E4h]
  int v3; // [rsp+10h] [rbp-4C1E0h]
  char v4; // [rsp+14h] [rbp-4C1DCh]
  unsigned __int8 v5; // [rsp+18h] [rbp-4C1D8h]
  int v6; // [rsp+1Ch] [rbp-4C1D4h]
  int v7; // [rsp+28h] [rbp-4C1C8h]
  int v8; // [rsp+2Ch] [rbp-4C1C4h]
  int v9; // [rsp+30h] [rbp-4C1C0h]
  int v10; // [rsp+34h] [rbp-4C1BCh]
  int v11; // [rsp+38h] [rbp-4C1B8h]
  char v12; // [rsp+3Ch] [rbp-4C1B4h]
  unsigned __int8 v13; // [rsp+40h] [rbp-4C1B0h]
  int v14; // [rsp+44h] [rbp-4C1ACh]
  int v15; // [rsp+48h] [rbp-4C1A8h]
  unsigned __int8 val; // [rsp+4Ch] [rbp-4C1A4h]
  int vala; // [rsp+4Ch] [rbp-4C1A4h]
  int valb; // [rsp+4Ch] [rbp-4C1A4h]
  int valc; // [rsp+4Ch] [rbp-4C1A4h]
  int vald; // [rsp+4Ch] [rbp-4C1A4h]
  int sharp; // [rsp+50h] [rbp-4C1A0h]
  int col; // [rsp+54h] [rbp-4C19Ch]
  int cola; // [rsp+54h] [rbp-4C19Ch]
  int colb; // [rsp+54h] [rbp-4C19Ch]
  int colc; // [rsp+54h] [rbp-4C19Ch]
  int row; // [rsp+58h] [rbp-4C198h]
  int rowa; // [rsp+58h] [rbp-4C198h]
  int rowb; // [rsp+58h] [rbp-4C198h]
  int rowc; // [rsp+58h] [rbp-4C198h]
  int rb; // [rsp+5Ch] [rbp-4C194h]
  unsigned __int8 pixel[484][644]; // [rsp+60h] [rbp-4C190h] BYREF

  val = 0;
  getbithuff(-1, 0LL);
  memset(pixel, 128, sizeof(pixel));
  for ( row = 2; row < (unsigned __int16)height + 2; ++row )
  {
    for ( col = (row & 1) + 2; col < (unsigned __int16)width + 2; col += 2 )
    {
      v15 = (pixel[row - 1][col + 642] + 2 * pixel[row - 1][col + 1] + pixel[row - 1][col - 1]) >> 2;
      vala = quicktake_100_load_raw_gstep[getbithuff(4, 0LL)] + v15;
      if ( vala >= 255 )
        v14 = 255;
      else
        v14 = vala;
      if ( v14 >= 0 )
      {
        if ( vala >= 255 )
          v12 = -1;
        else
          v12 = vala;
        v13 = v12;
      }
      else
      {
        v13 = 0;
      }
      val = v13;
      pixel[row][col] = v13;
      if ( col < 4 )
      {
        pixel[row + 1][(row & 1) == 0] = v13;
        pixel[row - 1][col + 642] = v13;
      }
      if ( row == 2 )
      {
        pixel[1][col + 3] = v13;
        pixel[1][col + 1] = v13;
      }
    }
    pixel[row][col] = val;
  }
  for ( rb = 0; rb < 2; ++rb )
  {
    for ( rowa = rb + 2; rowa < (unsigned __int16)height + 2; rowa += 2 )
    {
      for ( cola = 3 - (rowa & 1); cola < (unsigned __int16)width + 2; cola += 2 )
      {
        if ( rowa >= 4 && cola >= 4 )
        {
          valb = abs32(pixel[rowa - 1][cola + 642] - pixel[rowa - 2][cola - 2])
               + abs32(pixel[rowa - 2][cola] - pixel[rowa - 2][cola - 2])
               + abs32(pixel[rowa - 2][cola] - pixel[rowa - 1][cola + 642]);
          if ( valb >= 4 )
          {
            if ( valb >= 8 )
            {
              if ( valb >= 16 )
              {
                if ( valb >= 32 )
                {
                  v0 = 5;
                  if ( valb < 48 )
                    v0 = 4;
                  v8 = v0;
                }
                else
                {
                  v8 = 3;
                }
                v9 = v8;
              }
              else
              {
                v9 = 2;
              }
              v10 = v9;
            }
            else
            {
              v10 = 1;
            }
            v11 = v10;
          }
          else
          {
            v11 = 0;
          }
          sharp = v11;
        }
        else
        {
          sharp = 2;
        }
        v7 = (pixel[rowa - 1][cola + 642] + pixel[rowa - 2][cola]) >> 1;
        valc = quicktake_100_load_raw_rstep[4 * sharp + getbithuff(2, 0LL)] + v7;
        if ( valc >= 255 )
          v6 = 255;
        else
          v6 = valc;
        if ( v6 >= 0 )
        {
          if ( valc >= 255 )
            v4 = -1;
          else
            v4 = valc;
          v5 = v4;
        }
        else
        {
          v5 = 0;
        }
        pixel[rowa][cola] = v5;
        if ( rowa < 4 )
          pixel[rowa - 2][cola + 2] = v5;
        if ( cola < 4 )
          pixel[rowa + 1][cola + 642] = v5;
      }
    }
  }
  for ( rowb = 2; rowb < (unsigned __int16)height + 2; ++rowb )
  {
    for ( colb = 3 - (rowb & 1); colb < (unsigned __int16)width + 2; colb += 2 )
    {
      vald = ((pixel[rowb][colb + 1] + 4 * pixel[rowb][colb] + pixel[rowb - 1][colb + 643]) >> 1) - 256;
      if ( vald >= 255 )
        v3 = 255;
      else
        v3 = ((pixel[rowb][colb + 1] + 4 * pixel[rowb][colb] + pixel[rowb - 1][colb + 643]) >> 1) - 256;
      if ( v3 >= 0 )
      {
        if ( vald >= 255 )
          LOBYTE(v1) = -1;
        else
          v1 = ((pixel[rowb][colb + 1] + 4 * pixel[rowb][colb] + pixel[rowb - 1][colb + 643]) >> 1) - 256;
        v2 = v1;
      }
      else
      {
        v2 = 0;
      }
      pixel[rowb][colb] = v2;
    }
  }
  for ( rowc = 0; rowc < (unsigned __int16)height; ++rowc )
  {
    for ( colc = 0; colc < (unsigned __int16)width; ++colc )
      *((_WORD *)raw_image + colc + (unsigned __int16)raw_width * rowc) = quicktake_100_load_raw_t_curve[pixel[rowc + 2][colc + 2]];
  }
  maximum = 1023;
}