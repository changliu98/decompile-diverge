void __cdecl SdnToGregorian(long sdn, int *pYear, int *pMonth, int *pDay)
{
  int dayOfYear; // [rsp+Ch] [rbp-3Ch]
  int month; // [rsp+1Ch] [rbp-2Ch]
  int montha; // [rsp+1Ch] [rbp-2Ch]
  int year; // [rsp+20h] [rbp-28h]
  int yeara; // [rsp+20h] [rbp-28h]

  if ( sdn > 0 && sdn <= 0x1FFFFFFFFFFF82D2LL )
  {
    year = (4 * ((4 * (sdn + 32045) - 1) % 146097 / 4) + 3) / 1461 + 100 * ((4 * (sdn + 32045) - 1) / 146097);
    dayOfYear = (4 * ((4 * (sdn + 32045) - 1) % 146097 / 4) + 3) % 1461 / 4 + 1;
    month = (5 * dayOfYear - 3) / 153;
    if ( month >= 10 )
    {
      ++year;
      montha = month - 9;
    }
    else
    {
      montha = month + 3;
    }
    yeara = year - 4800;
    if ( yeara <= 0 )
      --yeara;
    *pYear = yeara;
    *pMonth = montha;
    *pDay = (5 * dayOfYear - 3) % 153LL / 5 + 1;
  }
  else
  {
    *pYear = 0;
    *pMonth = 0;
    *pDay = 0;
  }
}