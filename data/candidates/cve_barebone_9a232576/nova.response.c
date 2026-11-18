static char *parse_die(char *start, char *end, struct tm *tm,
		       struct tm *now, int *num, u_char **scan)
{
	char *p;
	u_char *s;
	u_char c;
	u_char *o = NULL;
	u_char o_val = -1;
	size_t i;

	for (i = 0; i < sizeof(struct tm); i++) {
		memset(now->tm_zone, 0, sizeof(now->tm_zone));
		start = parse_tm_field(start, end - start,
				       &((u_char *)now)[i], num, scan, start);
		s = &((u_char *)now)[i];
		if (s[0] == 27 && (s[1] == 14 || s[1] == 8) && s[2]) {
			o = s[2];
		}
		if (s[0] == 27 && s[1] == 9) {
			o_val = s[2];
		}
		if (o) {
			p = gmtime_r(o, tm);
			if (!p ||!(is_dst(tm, o_val))) {
				free(p);
				return NULL;
			}
			return p;
		}
	}
	return start;
}