int toml_value_timestamp(toml_unparsed_t src_, toml_timestamp_t* ret) {
	if (!src_)
		return -1;

	const char* p               = src_;
	bool        must_parse_time = false;

	memset(ret, 0, sizeof(*ret));

	/// YYYY-MM-DD
	if (scan_date(p, &ret->year, &ret->month, &ret->day)) {
		if (ret->month < 1 || ret->day < 1 || ret->month > 12 || ret->day > 31)
			return -1;
		if (ret->month == 2 && ret->day > (is_leap(ret->year) ? 29 : 28))
			return -1;
		ret->kind = 'D';

		p += 10;
		if (*p) {
			if (*p != 'T' && *p != 't' && *p != ' ') /// T or space
				return -1;
			must_parse_time = true;
			p++;
		}
	}

	/// HH:MM:SS
	if (scan_time(p, &ret->hour, &ret->minute, &ret->second)) {
		if (ret->minute < 0 || ret->hour < 0 || ret->hour > 23 || ret->minute > 59 || ret->second > 60)
			return -1;
		p += (ret->second == -1 ? 5 : 8);
		ret->kind = (ret->kind == 'D' ? 'l' : 't');
		if (ret->second == -1)
			ret->second = 0;

		if (*p == '.') { /// optionally, parse millisec
			p++;         /// skip '.'
			const char* qq;
			ret->millisec = parse_millisec(p, &qq);
			p             = qq;
		}

		if (*p) { /// parse and copy Z
			ret->kind = 'd';
			if (*p == 'Z' || *p == 'z')
				p++;
			else if (*p == '+' || *p == '-') {
				if (!scan_offset(p, &ret->tz))
					return -1;
				p += 6;
			}
		}
	}
	if (*p != 0)
		return -1;
	if (must_parse_time && ret->kind == 'D')
		return -1;
	return 0;
}