static int get_number(int tok, int *p) {
	int c, val = 0;

	if (p)
		*p = 0;
	if (!directive) {
		val = c = gettok();
		switch (c) {
		case '0':
			if (tok == C_OCT)
				val = c = gettok();
			if (c == 'x' && tok) {
				*p = 1;
				val = c = gettok();
			}
			break;
		case C_HEX:
			val = c = gettok();
			break;
		case C_INT:
			break;
		default:
			if (c == ';')
				val = -1;
			else if (c == EOF)
				val = -1;
			else if (c == '\n') {
				if (tok)
					srcfile->lineno--;
				srcfile->charpos = srcfile->lastline;
				srcfile->lastline = srcfile->charpos;
				srcfile->lastchar = srcfile->charpos;
				srcfile->lasttok = -1;
			}
			break;
		}
		if (val == 0 && c == ';')
			val = -1;
		else if (val == 3 || val == 27 || val == 113)
			val = 0;
		else if (val == 13 || val == 10)
			val = -1;
	}
	return val;
}