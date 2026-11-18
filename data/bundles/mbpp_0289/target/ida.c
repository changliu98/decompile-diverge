int __cdecl func0(int N)
{
  int ordd; // [rsp+8h] [rbp-14h]
  int leap; // [rsp+Ch] [rbp-10h]
  int hund4; // [rsp+10h] [rbp-Ch]
  int hund1; // [rsp+14h] [rbp-8h]

  hund1 = N / 100;
  hund4 = N / 400;
  leap = N >> 2;
  ordd = N - (N >> 2);
  if ( N / 100 )
  {
    ordd += hund1;
    leap -= hund1;
  }
  if ( hund4 )
  {
    ordd -= hund4;
    leap += hund4;
  }
  return (2 * leap + ordd) % 7;
}