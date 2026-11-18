size_t modp_rtrim(char *s, size_t len)
{
	while (len) {
		char c = s[len - 1];
		if (c!='' && c!= '\n' && c!= '\t' && c!= '\r')
			break;
		s[--len] = 0;
	}
	return len;
}