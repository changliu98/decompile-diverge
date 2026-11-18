int toml_value_timestamp(const char *src, toml_timestamp *ts) {
  if (src == NULL) {
    return -1;
  }
  const char *p = src;
  int has_date = 0;
  memset(ts, 0, sizeof(toml_timestamp));
  if (scan_date(p, &ts->year, &ts->month, &ts->day)) {
    if (ts->month < 1 || ts->day < 1 || ts->month > 12 || ts->day > 31) {
      return -1;
    }
    if (ts->month == 2) {
      int day = ts->day;
      int max_day = is_leap(ts->year) ? 29 : 28;
      if (day > max_day) {
        return -1;
      }
    }
    ts->type = 'D';
    p += 10;
    if (*p != '\0') {
      if (*p != 'T' && *p != 't' && *p != ' ') {
        return -1;
      }
      has_date = 1;
      p++;
    }
  }
  if (scan_time(p, &ts->hour, &ts->min, &ts->sec)) {
    if (ts->min < 0 || ts->hour > 23 || ts->min > 59 || ts->sec > 60) {
      return -1;
    }
    p += (ts->sec == -1) ? 5 : 8;
    ts->type = (ts->type == 'D') ? 'l' : 't';
    if (ts->sec == -1) {
      ts->sec = 0;
    }
    if (*p == '.') {
      const char *end;
      ts->millisec = parse_millisec(++p, &end);
      p = end;
    }
    if (*p != '\0') {
      ts->type = 'd';
      if (*p == 'Z' || *p == 'z') {
        p++;
      } else if (*p == '+' || *p == '-') {
        if (!scan_offset(p, &ts->offset)) {
          return -1;
        }
        p += 6;
      }
    }
  }
  if (*p != '\0') {
    return -1;
  }
  if (has_date && ts->type == 'D') {
    return -1;
  }
  return 0;
}