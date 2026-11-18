void __cdecl SdnToJulian(long sdn, int *pYear, int *pMonth, int *pDay)
{
  __int64 yearl; // [rsp+0h] [rbp-48h]
  int dayOfYear; // [rsp+Ch] [rbp-3Ch]
  int month; // [rsp+20h] [rbp-28h]
  int montha; // [rsp+20h] [rbp-28h]
  int year; // [rsp+24h] [rbp-24h]
  int yeara; // [rsp+24h] [rbp-24h]

  if ( sdn > 0
    && sdn <= 0x1FFFFFFFFFFF82ADLL
    && (yearl = (4 * sdn + 128331) / 1461, yearl <= 0x7FFFFFFF)
    && yearl >= (__int64)0xFFFFFFFF80000000LL )
  {
    year = (4 * sdn + 128331) / 1461;
    dayOfYear = (4 * sdn + 128331) % 1461 / 4 + 1;
    month = (5 * dayOfYear - 3) / 153;
    if ( month >= 10 )
    {
      year = yearl + 1;
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