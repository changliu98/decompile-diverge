int __cdecl cp_unfilter(int w, int h, int bpp, uint8_t *raw)
{
  uint8_t *v4; // rax
  int y; // [rsp+10h] [rbp-30h]
  int x; // [rsp+14h] [rbp-2Ch]
  int xa; // [rsp+14h] [rbp-2Ch]
  int xb; // [rsp+14h] [rbp-2Ch]
  int xc; // [rsp+14h] [rbp-2Ch]
  int xd; // [rsp+14h] [rbp-2Ch]
  int xe; // [rsp+14h] [rbp-2Ch]
  int xf; // [rsp+14h] [rbp-2Ch]
  uint8_t *prev; // [rsp+18h] [rbp-28h]
  int len; // [rsp+24h] [rbp-1Ch]
  uint8_t *rawa; // [rsp+28h] [rbp-18h]
  uint8_t *rawb; // [rsp+28h] [rbp-18h]
  uint8_t *rawc; // [rsp+28h] [rbp-18h]
  int v20; // [rsp+3Ch] [rbp-4h]

  rawa = raw;
  len = bpp * w;
  if ( h <= 0 )
  {
LABEL_16:
    prev = rawa;
    rawb = &rawa[len];
    y = 1;
    while ( 2 )
    {
      if ( y < h )
      {
        v4 = rawb;
        rawc = rawb + 1;
        switch ( *v4 )
        {
          case 0u:
            goto LABEL_44;
          case 1u:
            for ( xc = 0; xc < bpp; ++xc )
              rawc[xc] = rawc[xc];
            while ( xc < len )
            {
              rawc[xc] += rawc[xc - bpp];
              ++xc;
            }
            goto LABEL_44;
          case 2u:
            for ( xd = 0; xd < bpp; ++xd )
              rawc[xd] += prev[xd];
            while ( xd < len )
            {
              rawc[xd] += prev[xd];
              ++xd;
            }
            goto LABEL_44;
          case 3u:
            for ( xe = 0; xe < bpp; ++xe )
              rawc[xe] += prev[xe] / 2;
            while ( xe < len )
            {
              rawc[xe] += (prev[xe] + rawc[xe - bpp]) / 2;
              ++xe;
            }
            goto LABEL_44;
          case 4u:
            for ( xf = 0; xf < bpp; ++xf )
              rawc[xf] += prev[xf];
            while ( xf < len )
            {
              rawc[xf] += cp_paeth(rawc[xf - bpp], prev[xf], prev[xf - bpp]);
              ++xf;
            }
LABEL_44:
            ++y;
            prev = rawc;
            rawb = &rawc[len];
            continue;
          default:
            return 0;
        }
      }
      return 1;
    }
  }
  else
  {
    rawa = raw + 1;
    switch ( *raw )
    {
      case 0u:
      case 2u:
        goto LABEL_16;
      case 1u:
        for ( x = bpp; x < len; ++x )
          rawa[x] += rawa[x - bpp];
        goto LABEL_16;
      case 3u:
        for ( xa = bpp; xa < len; ++xa )
          rawa[xa] += rawa[xa - bpp] / 2;
        goto LABEL_16;
      case 4u:
        for ( xb = bpp; xb < len; ++xb )
          rawa[xb] += cp_paeth(rawa[xb - bpp], 0, 0);
        goto LABEL_16;
      default:
        v20 = 0;
        break;
    }
  }
  return v20;
}