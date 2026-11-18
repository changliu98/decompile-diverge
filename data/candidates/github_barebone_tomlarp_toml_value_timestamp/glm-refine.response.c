int __cdecl toml_value_timestamp(toml_unparsed_t src, toml_timestamp_t *ret)
{
  const char *p;
  const char *endp;
  bool must_parse_time = false;

  if (!src)
    return -1;

  p = src;
  memset(ret, 0, sizeof(toml_timestamp_t));

  // 1. Try to parse Date (YYYY-MM-DD)
  if (scan_date(p, &ret->year, &ret->month, &ret->day))
  {
    if (ret->month < 1 || ret->day < 1 || ret->month > 12 || ret->day > 31)
      return -1;

    // February leap year validation
    if (ret->month == 2)
    {
      int max_feb_day = is_leap(ret->year) ? 29 : 28;
      if (ret->day > max_feb_day)
        return -1;
    }

    ret->kind = 'D'; // 68
    p += 10; // "YYYY-MM-DD" is exactly 10 characters

    if (*p)
    {
      // Valid separators between date and time: 'T', 't', or ' '
      if (*p != 'T' && *p != 't' && *p != ' ')
        return -1;
      must_parse_time = true;
      ++p;
    }
  }

  // 2. Try to parse Time (HH:MM:SS)
  if (scan_time(p, &ret->hour, &ret->minute, &ret->second))
  {
    if (ret->minute < 0 || ret->hour > 23 || ret->minute > 59 || ret->second > 60)
      return -1;

    // scan_time parses either "HH:MM" (5 chars) or "HH:MM:SS" (8 chars)
    p += (ret->second == -1) ? 5 : 8;

    // Update kind: 'l' (108) for local datetime, 't' (116) for time only
    ret->kind = (ret->kind == 'D') ? 'l' : 't';

    if (ret->second == -1)
      ret->second = 0;

    // 3. Try to parse fractional seconds (.nnnnnn)
    if (*p == '.')
    {
      ret->millisec = parse_millisec(++p, &endp);
      p = endp;
    }

    // 4. Try to parse Timezone offset
    if (*p)
    {
      ret->kind = 'd'; // 100 - datetime with offset
      if (*p == 'Z' || *p == 'z')
      {
        ++p;
      }
      else if (*p == '+' || *p == '-')
      {
        if (!scan_offset(p, &ret->tz))
          return -1;
        p += 6; // "+HH:MM" or "-HH:MM" is exactly 6 characters
      }
    }
  }

  // 5. Final validations
  if (*p)
    return -1;

  // If a 'T' was found after the date, a time must have been parsed
  if (must_parse_time && ret->kind == 'D')
    return -1;

  return 0;
}