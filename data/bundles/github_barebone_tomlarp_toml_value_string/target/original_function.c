int toml_value_string(toml_unparsed_t src, char** ret, int* len) {
	bool        multiline = false;
	const char* sp;
	const char* sq;

	*ret = 0;
	if (!src)
		return -1;

	/// First char must be a s-quote or d-quote
	int qchar  = src[0];
	int srclen = strlen(src);
	if (!(qchar == '\'' || qchar == '"')) {
		return -1;
	}

	/// triple quotes?
	if (qchar == src[1] && qchar == src[2]) {
		multiline = true;             /// triple-quote implies multiline
		sp        = src + 3;          /// first char after quote
		sq        = src + srclen - 3; /// first char of ending quote

		if (!(sp <= sq && sq[0] == qchar && sq[1] == qchar && sq[2] == qchar))
			return -1; /// last 3 chars in src must be qchar

		if (sp[0] == '\n') /// skip new line immediate after qchar
			sp++;
		else if (sp[0] == '\r' && sp[1] == '\n')
			sp += 2;
	} else {
		sp = src + 1;                    /// first char after quote
		sq = src + srclen - 1;           /// ending quote
		if (!(sp <= sq && *sq == qchar)) /// last char in src must be qchar
			return -1;
	}

	/// at this point:
	///     sp points to first valid char after quote.
	///     sq points to one char beyond last valid char.
	///     string len is (sq - sp).
	if (qchar == '\'')
		*ret = norm_lit_str(sp, sq - sp, len, multiline, 0, 0);
	else
		*ret = norm_basic_str(sp, sq - sp, len, multiline, 0, 0);
	return *ret ? 0 : -1;
}