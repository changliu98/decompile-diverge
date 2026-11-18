void __cdecl gsdate(int day, int mon, int year, int *serial)
{
  int i; // [rsp+0h] [rbp-1Ch]
  int yeara; // [rsp+10h] [rbp-Ch]
  int mona; // [rsp+14h] [rbp-8h]

  yeara = year + 100;
  if ( mon <= 2 )
  {
    mona = mon + 9;
    yeara = year + 99;
  }
  else
  {
    mona = mon - 3;
  }
  i = day + (153 * mona + 2) / 5 + 1461 * yeara / 4 - 36466;
  if ( i > 59 )
    i = day + (153 * mona + 2) / 5 + 1461 * yeara / 4 - 36467;
  *serial = i;
}