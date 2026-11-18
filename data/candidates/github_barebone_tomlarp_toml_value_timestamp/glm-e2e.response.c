int toml_value_timestamp(const char *str, struct toml_timestamp *ts) {
    int ret = -1;
    const char *p = str;
    char has_time = 0;
    const char *end;

    if (!str) {
        return -1;
    }

    memset(ts, 0, 0x24);

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
        ts->tag = 'D';
        p += 10;
        if (*p != '\0') {
            if (*p == 'T' || *p == 't' || *p == ' ') {
                has_time = 1;
                p++;
            } else {
                return -1;
            }
        }
    }

    if (scan_time(p, &ts->hour, &ts->minute, &ts->second)) {
        if (ts->minute < 0 || ts->hour < 0 || ts->hour > 23 || 
            ts->minute > 59 || ts->second > 60) {
            return -1;
        }
        
        int offset = (ts->second == -1) ? 5 : 8;
        p += offset;
        
        ts->tag = (ts->tag == 'D') ? 'l' : 't';
        
        if (ts->second == -1) {
            ts->second = 0;
        }
        
        if (*p == '.') {
            p++;
            ts->millisec = parse_millisec(p, &end);
            p = end;
        }
        
        if (*p != '\0') {
            ts->tag = 'd';
            if (*p == 'Z' || *p == 'z') {
                p++;
            } else if (*p == '+' || *p == '-') {
                if (!scan_offset(p, ts->offset)) {
                    return -1;
                }
                p += 6;
            }
        }
    }

    if (*p != '\0') {
        return -1;
    }

    if (has_time && ts->tag == 'D') {
        return -1;
    }

    return 0;
}