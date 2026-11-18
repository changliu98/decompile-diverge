int
func0(const char *s1, const char *s2, size_t n)
{
	const unsigned char *us1 = (const unsigned char *)s1;
	const unsigned char *us2 = (const unsigned char *)s2;
	int ret = 0;

	if (us1 == us2 || n == 0)
		return (0);

	while (--n > 0) {
		unsigned char u1 = EVUTIL_TOLOWER_(*us1);
		unsigned char u2 = EVUTIL_TOLOWER_(*us2);
		++us1; ++us2;
		if (u1 == u2) {
			if (u1 == '\0')
				break;
			continue;
		}
		ret = (int)u1 - (int)u2;
		break;
	}

	return (ret);
}