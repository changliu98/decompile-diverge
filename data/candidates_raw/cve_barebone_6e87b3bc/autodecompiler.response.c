void quicktake_100_load_raw()
{
  unsigned char *diff, *edge, *fedge, *huff;
  int diffp, edgep, fedgep, huffp;
  unsigned char data[644][644];
  int i, j, k, l, m, n, p, q, r, s, t, u, v, w, x, y, z;

  for (k=0; k<644; k++)
    for (l=0; l<644; l++)
      data[k][l] = 0x80;

  getbithuff(-1, huff);
  for (k=2; k<height+2; k++)
    for (l=2+(k%2); l<width+2; l+=2)
      {
        m = (data[k-1][l-1] + data[k-1][l+1]*2 + data[k][l-2]) >> 2;
        n = getbithuff(4, huff);
        m += quicktake_100_load_raw_gstep[n];
        if (m < 0) m = 0;
        if (m > 255) m = 255;
        data[k][l] = m;
        if (l < 5)
          {
            data[k+1][l^1] = data[k][l];
            data[k][l-2] = data[k][l];
          }
        if (k == 2)
          {
            data[k-1][l+3] = data[k][l];
            data[k-1][l+1] = data[k][l];
          }
      }

  for (t=0; t<2; t++)
    for (k=2+t; k<height+2; k+=2)
      for (l=2+(k%2); l<width+2; l+=2)
        {
          if (k < 5 || l < 5)
            m = 2;
          else
            m = ((((data[k-2][l-2] - data[k-2][l]) ^ ((data[k-2][l-2] - data[k-2][l]) >> 31)) - ((data[k-2][l-2] - data[k-2][l]) >> 31)) + (((data[k-2][l-2] - data[k][l-2]) ^ ((data[k-2][l-2] - data[k][l-2]) >> 31)) - ((data[k-2][l-2] - data[k][l-2]) >> 31))) + (((data[k-2][l-2] - data[k][l]) ^ ((data[k-2][l-2] - data[k][l]) >> 31)) - ((data[k-2][l-2] - data[k][l]) >> 31));
          if (m < 5) m = 0;
          if (m < 9) n = 1;
          else if (m < 16) n = 2;
          else if (m < 32) n = 3;
          else if (m < 48) n = 4;
          else n = 5;
          m = (data[k-2][l] + data[k][l-2]) >> 1;
          diff = &quicktake_100_load_raw_rstep[n];
          m += diff[getbithuff(2, huff)];
          if (m < 0) m = 0;
          if (m > 255) m = 255;
          data[k][l] = m;
          if (k < 5)
            data[k-2][l+2] = data[k][l];
          if (l < 5)
            data[k+2][l-2] = data[k][l];
        }

  for (k=2; k<height+2; k++)
    for (l=2+(k%2); l<width+2; l+=2)
      {
        m = (data[k][l-1] + data[k][l+1]*4 + data[k][l+1]) >> 1;
        m -= 256;
        if (m < 0) m = 0;
        if (m > 255) m = 255;
        data[k][l] = m;
      }

  for (k=0; k<height; k++)
    for (l=0; l<width; l++)
      raw_image[(k)*raw_width + (l)] = (short)quicktake_100_load_raw_t_curve[data[k+2][l+2]];
  maximum = 1023;
}