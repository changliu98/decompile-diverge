double __cdecl func0(double number)
{
  double g2; // [rsp+8h] [rbp-20h]
  double g; // [rsp+10h] [rbp-18h]

  if ( number == 0.0 )
    return 0.0;
  g = number / 2.0;
  g2 = number / 2.0 + 1.0;
  while ( g != g2 )
  {
    g2 = g;
    g = (g + number / g) / 2.0;
  }
  return g;
}