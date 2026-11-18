void __cdecl rgb2hsv(double r, double g, double b, double *h, double *s, double *v)
{
  double v6; // [rsp+0h] [rbp-A8h]
  double v7; // [rsp+8h] [rbp-A0h]
  double v8; // [rsp+10h] [rbp-98h]
  double v9; // [rsp+20h] [rbp-88h]
  double v10; // [rsp+28h] [rbp-80h]
  double v11; // [rsp+30h] [rbp-78h]
  double st; // [rsp+40h] [rbp-68h]
  double ht; // [rsp+48h] [rbp-60h]
  double gc; // [rsp+50h] [rbp-58h]
  double bc; // [rsp+58h] [rbp-50h]
  double rc; // [rsp+60h] [rbp-48h]

  ht = 0.0;
  st = 0.0;
  if ( b <= g )
    v11 = b;
  else
    v11 = g;
  if ( v11 <= r )
  {
    if ( b <= g )
      v9 = b;
    else
      v9 = g;
    v10 = v9;
  }
  else
  {
    v10 = r;
  }
  if ( g <= b )
    v8 = b;
  else
    v8 = g;
  if ( r <= v8 )
  {
    if ( g <= b )
      v6 = b;
    else
      v6 = g;
    v7 = v6;
  }
  else
  {
    v7 = r;
  }
  if ( v7 > 0.0 )
    st = (v7 - v10) / v7;
  if ( st > 0.0 )
  {
    rc = (v7 - r) / (v7 - v10);
    gc = (v7 - g) / (v7 - v10);
    bc = (v7 - b) / (v7 - v10);
    if ( r == v7 )
    {
      ht = bc - gc;
    }
    else if ( g == v7 )
    {
      ht = rc + 2.0 - bc;
    }
    else if ( b == v7 )
    {
      ht = gc + 4.0 - rc;
    }
    ht = 60.0 * ht;
    if ( ht < 0.0 )
      ht = ht + 360.0;
  }
  *h = ht / 360.0;
  *v = v7;
  *s = st;
}