int lowercase(int ch) {
	if ('A' <= ch && ch <= 'Z')
		return ch - 'A' + 'a';
	return ch;
}