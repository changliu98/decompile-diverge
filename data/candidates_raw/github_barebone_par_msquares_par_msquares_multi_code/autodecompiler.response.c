static int
get_color_pair(int sw, int se, int ne, int nw)
{
 int c = 0;
 int cp[4];

 cp[0] = c++;
 if (se == sw)
  cp[1] = cp[0];
 else
  cp[1] = c++;

 if (ne == se)
  cp[2] = cp[1];
 else if (ne == sw)
  cp[2] = cp[0];
 else
  cp[2] = c++;

 if (nw == ne)
  cp[3] = cp[2];
 else if (nw == se)
  cp[3] = cp[1];
 else if (nw == sw)
  cp[3] = cp[0];
 else
  cp[3] = c++;

 return (cp[0] | (cp[1] << 2) | (cp[2] << 4) | (cp[3] << 6));
}