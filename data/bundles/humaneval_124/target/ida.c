int __cdecl func0(const char *date)
{
  char str_year[5]; // [rsp+5h] [rbp-2Bh] BYREF
  char str_day[3]; // [rsp+Ah] [rbp-26h] BYREF
  char str_month[3]; // [rsp+Dh] [rbp-23h] BYREF
  int i; // [rsp+10h] [rbp-20h]
  int yy; // [rsp+14h] [rbp-1Ch]
  int dd; // [rsp+18h] [rbp-18h]
  int mm; // [rsp+1Ch] [rbp-14h]
  const char *datea; // [rsp+20h] [rbp-10h]

  datea = date;
  if ( strlen(date) != 10 )
    return 0;
  for ( i = 0; i < 10; ++i )
  {
    if ( i == 2 || i == 5 )
    {
      if ( datea[i] != 45 )
        return 0;
    }
    else if ( datea[i] < 48 || datea[i] > 57 )
    {
      return 0;
    }
  }
  str_month[0] = *datea;
  str_month[1] = datea[1];
  str_month[2] = 0;
  str_day[0] = datea[3];
  str_day[1] = datea[4];
  str_day[2] = 0;
  str_year[0] = datea[6];
  str_year[1] = datea[7];
  str_year[2] = datea[8];
  str_year[3] = datea[9];
  str_year[4] = 0;
  mm = atoi(str_month);
  dd = atoi(str_day);
  yy = atoi(str_year);
  if ( mm < 1 || mm > 12 )
    return 0;
  if ( dd < 1 || dd > 31 )
    return 0;
  if ( (mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd == 31 )
    return 0;
  return mm != 2 || dd <= 29;
}