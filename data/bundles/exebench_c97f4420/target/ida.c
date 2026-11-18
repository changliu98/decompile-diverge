void __cdecl get_month_and_day_by_row(const int row, const int year, int *const month, int *const day)
{
  int v4; // eax
  bool v5; // [rsp+Fh] [rbp-51h]
  int days_in_month[12]; // [rsp+10h] [rbp-50h] BYREF
  int is_leap; // [rsp+40h] [rbp-20h]
  int monthdays; // [rsp+44h] [rbp-1Ch]
  int *daya; // [rsp+48h] [rbp-18h]
  int *montha; // [rsp+50h] [rbp-10h]
  int yeara; // [rsp+58h] [rbp-8h]
  int rowa; // [rsp+5Ch] [rbp-4h]

  rowa = row;
  yeara = year;
  montha = month;
  daya = day;
  memcpy(days_in_month, &unk_2030, sizeof(days_in_month));
  *daya = 0;
  *montha = 0;
  monthdays = 0;
  if ( yeara % 4 || (v5 = 1, !(yeara % 100)) )
    v5 = yeara % 400 == 0;
  is_leap = v5;
  if ( rowa > 0 && rowa <= is_leap + 365 )
  {
    if ( is_leap )
      ++days_in_month[1];
    while ( rowa > monthdays )
    {
      v4 = (*montha)++;
      monthdays += days_in_month[v4];
    }
    *daya = days_in_month[*montha - 1] + rowa - monthdays;
  }
}