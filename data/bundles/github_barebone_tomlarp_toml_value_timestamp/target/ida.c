int __cdecl toml_value_timestamp(toml_unparsed_t src_, toml_timestamp_t *ret)
{
  bool v2; // si
  int v3; // ecx
  int v4; // ecx
  char v5; // al
  int v6; // eax
  int day; // [rsp+Ch] [rbp-34h]
  const char *qq; // [rsp+10h] [rbp-30h] BYREF
  bool must_parse_time; // [rsp+1Fh] [rbp-21h]
  const char *p; // [rsp+20h] [rbp-20h]
  toml_timestamp_t *reta; // [rsp+28h] [rbp-18h]
  toml_unparsed_t src_a; // [rsp+30h] [rbp-10h]

  src_a = src_;
  reta = ret;
  if ( !src_ )
    return -1;
  p = src_a;
  must_parse_time = 0;
  memset(reta, 0, sizeof(toml_timestamp_t));
  if ( scan_date(src_a, &reta->year, &reta->month, &reta->day) )
  {
    if ( reta->month < 1 || reta->day < 1 || reta->month > 12 || reta->day > 31 )
      return -1;
    if ( reta->month == 2 )
    {
      day = reta->day;
      v2 = is_leap(reta->year);
      v3 = 28;
      if ( v2 )
        v3 = 29;
      if ( day > v3 )
        return -1;
    }
    reta->kind = 68;
    p += 10;
    if ( *p )
    {
      if ( *p != 84 && *p != 116 && *p != 32 )
        return -1;
      must_parse_time = 1;
      ++p;
    }
  }
  if ( scan_time(p, &reta->hour, &reta->minute, &reta->second) )
  {
    if ( reta->minute < 0 || reta->hour > 0x17u || reta->minute > 59 || reta->second > 60 )
      return -1;
    v4 = 8;
    if ( reta->second == -1 )
      v4 = 5;
    p += v4;
    v5 = 116;
    if ( reta->kind == 68 )
      v5 = 108;
    reta->kind = v5;
    if ( reta->second == -1 )
      reta->second = 0;
    if ( *p == 46 )
    {
      v6 = parse_millisec(++p, &qq);
      reta->millisec = v6;
      p = qq;
    }
    if ( *p )
    {
      reta->kind = 100;
      if ( *p == 90 || *p == 122 )
      {
        ++p;
      }
      else if ( *p == 43 || *p == 45 )
      {
        if ( !scan_offset(p, &reta->tz) )
          return -1;
        p += 6;
      }
    }
  }
  if ( *p )
    return -1;
  if ( must_parse_time && reta->kind == 68 )
    return -1;
  return 0;
}