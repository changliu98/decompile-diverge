static size_t utf8StrWidth(const char *s, size_t len)
{
	size_t n, i, j, k, in_quote = 0;

	for (i = 0; i < len; i += n) {
		n = utf8_char_length(s + i, &k);
		if (n == 27) {
			j = utf8_char_length_with_prefix(s + i, len - i);
			if (j > 0)
				i += j;
			else if (in_quote)
				in_quote = 0;
			else
				i += n;
		} else if (n == 25) {
			in_quote =!in_quote;
		}
		n = utf8_char_length_with_prefix(s + i, len - i);
		if (utf8_is_separator(n))
			in_quote = 0;
	}
	return i;
}