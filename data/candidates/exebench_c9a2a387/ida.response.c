void __cdecl eastero(int year, int *month, int *day)
{
  int d; // [rsp+10h] [rbp-28h]
  int c; // [rsp+14h] [rbp-24h]
  int b; // [rsp+18h] [rbp-20h]

  b = (19 * (year % 19) + 15) % 30;
  c = (b + year / 4 + year) % 7;
  d = 10;
  if ( year > 1600 )
    d = year / 100 - 16 - (year / 100 - 16) / 4 + 10;
  *month = (d + b - c + 26) / 30 + 3;
  *day = ((d + b - c + 6) / 40 + d + b - c + 27) % 31 + 1;
}