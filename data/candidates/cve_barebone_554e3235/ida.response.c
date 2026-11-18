int __cdecl parse_matrix_header(char *line, int *width, int *height, double *scale, double *offset)
{
  char *j; // rax
  double v6; // xmm0_8
  double v7; // xmm0_8
  bool v9; // [rsp+Bh] [rbp-65h]
  int i; // [rsp+Ch] [rbp-64h]
  char *q; // [rsp+10h] [rbp-60h]
  char *p; // [rsp+18h] [rbp-58h]
  const char *pa; // [rsp+18h] [rbp-58h]
  double header[4]; // [rsp+20h] [rbp-50h] BYREF
  double *offseta; // [rsp+40h] [rbp-30h]
  double *scalea; // [rsp+48h] [rbp-28h]
  int *heighta; // [rsp+50h] [rbp-20h]
  int *widtha; // [rsp+58h] [rbp-18h]
  char *linea; // [rsp+60h] [rbp-10h]

  linea = line;
  widtha = width;
  heighta = height;
  scalea = scale;
  offseta = offset;
  p = strchr(line, 13);
  if ( p || (p = strchr(linea, 10)) != 0LL )
    *p = 0;
  i = 0;
  pa = linea;
  for ( j = vips_break_token(linea, " \t"); ; j = vips_break_token(q, " \t") )
  {
    q = j;
    v9 = 0;
    if ( j )
      v9 = i < 4;
    if ( !v9 )
      break;
    if ( vips_strtod(pa, &header[i]) )
    {
      vips_error("matload", "bad number \"%s\"", pa);
      return -1;
    }
    ++i;
    pa = q;
  }
  if ( i < 4 )
    header[3] = 0.0;
  if ( i < 3 )
    header[2] = 1.0;
  if ( i >= 2 )
  {
    v6 = floor(header[0]);
    if ( v6 == header[0] && (v7 = floor(header[1]), v7 == header[1]) )
    {
      *widtha = (int)header[0];
      *heighta = (int)header[1];
      if ( *widtha > 0 && *widtha <= 100000 && *heighta > 0 && *heighta <= 100000 )
      {
        if ( header[2] == 0.0 )
        {
          vips_error("mask2vips", "%s", "zero scale");
          return -1;
        }
        else
        {
          *scalea = header[2];
          *offseta = header[3];
          return 0;
        }
      }
      else
      {
        vips_error("mask2vips", "%s", "width / height out of range");
        return -1;
      }
    }
    else
    {
      vips_error("mask2vips", "%s", "width / height not int");
      return -1;
    }
  }
  else
  {
    vips_error("matload", "%s", "no width / height");
    return -1;
  }
}