static bool pattern_match_custom_class(char c, char *s, char *e) {
	bool ret = true;
	bool neg = false;

	if (*++s == '^') {
		ret = false;
		s++;
	}

	while (++s < e) {
		if (*s == '%') {
			if (isxdigit (*(s+1))) {
				s += 2;
				continue;
			}
			ret =!ret;
			continue;
		}
		if (*s == '-') {
			if (s+2 < e && *(s+1) <= c && c <= *(s+2)) {
				ret =!neg;
				break;
			}
			ret = neg;
			break;
		}
		if (*s == c) {
			ret =!neg;
			break;
		}
		ret = neg;
	}

	return ret ^ 0xff;
}