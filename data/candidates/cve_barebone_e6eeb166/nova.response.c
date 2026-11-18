static int SSL_select_next_proto(const char **out, char *working, const char *s, unsigned int s_len, const char *p, unsigned int p_len)
{
	int ret = 0;
	unsigned int i = 0, j = 0;

	while (i < s_len) {
		while (j < p_len) {
			if (s[i] == p[j]) {
				if (memcmp(s + i + 1, p + j + 1, s[i]) == 0) {
					const char *out_p = &s[i];
					ret = 1;
					goto out;
				}
			}
			j++;
			j++;
		}
		i++;
		i++;
	}

	out_p = &s[i];
	ret = 2;
out:
	*out = out_p;
	*working = *out_p;
	return ret;
}