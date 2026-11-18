int toml_value_timestamp(char *s, struct toml_timestamp_t *ts)
{
    if (!s)
        return -1;
    char *p = s;
    int must_parse_time = 0;
    memset(ts, 0, sizeof *ts);
    if (scan_date(s, &ts->year, &ts->month, &ts->day)) {
        if (ts->month < 1 || ts->day < 1 ||
            ts->month > 12 || ts->day > 31)
            return -1;
        if (ts->month == 2) {
            int day = ts->day;
            if (day > (is_leap(ts->year) ? 29 : 28))
                return -1;
        }
        ts->kind = 'D';
        p += 10;
        if (*p) {
            if (*p != 'T' && *p != 't' && *p != ' ')
                return -1;
            must_parse_time = 1;
            p += 1;
        }
    }
    if (scan_time(p, &ts->hour, &ts->minute, &ts->second)) {
        if (ts->minute < 0 || ts->hour > 23 ||
            ts->minute > 59 || ts->second > 60)
            return -1;
        p += 8;
        ts->kind = 'T';
        if (ts->second == -1)
            ts->second = 0;
        if (*p == '.') {
            char *end;
            ts->millisec = parse_millisec(++p, &end);
            p = end;
        }
        if (*p) {
            ts->kind = 'd';
            if (*p == 'Z' || *p == 'z')
                p += 1;
            else if (*p == '+' || *p == '-') {
                if (!scan_offset(p, &ts->tz))
                    return -1;
                p += 6;
            }
        }
    }
    if (*p)
        return -1;
    if (must_parse_time && ts->kind == 'D')
        return -1;
    return 0;
}