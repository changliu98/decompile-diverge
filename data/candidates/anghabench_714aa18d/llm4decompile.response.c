int
is_valid_ref_char(char ch)
{
	if (ch <= ' ')
		return 0;
	if (ch == '*' || ch == ':' || ch == '?' || ch == '[' || ch == '\\' ||
	    ch == '^' || ch == '~')
		return 0;
	return 1;
}