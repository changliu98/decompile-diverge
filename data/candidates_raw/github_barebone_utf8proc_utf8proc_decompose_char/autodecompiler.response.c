__attribute__((used)) static int grapheme_break_extended(int lbc, int tbc, int cbc, int prev_cbc, int *last_boundclass) {
	int grapheme_break;
	if (lbc == 0 && tbc == 0 && cbc == 0)
		grapheme_break = 0;
	else if (lbc == 0 && tbc == 0 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 0 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 0 && tbc == 0 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 1 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 1 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 1 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 0 && tbc == 1 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 2 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 2 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 2 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 0 && tbc == 2 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 3 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 3 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 0 && tbc == 3 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 0 && tbc == 3 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 0 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 0 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 0 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 0 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 1 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 1 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 1 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 1 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 2 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 2 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 2 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 2 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 3 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 3 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 1 && tbc == 3 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 1 && tbc == 3 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 0 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 0 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 0 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 0 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 1 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 1 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 1 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 1 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 2 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 2 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 2 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 2 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 3 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 3 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 2 && tbc == 3 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 2 && tbc == 3 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 0 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 0 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 0 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 0 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 1 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 1 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 1 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 1 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 2 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 2 && cbc == 1)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 2 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 2 && cbc == 3)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 3 && cbc == 0)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 3 && cbc == 1)
		grapheme_break = 1;
	else if (lbc == 3 && tbc == 3 && cbc == 2)
		grapheme_break = 0;
	else if (lbc == 3 && tbc == 3 && cbc == 3)
		grapheme_break = 1;
	else
		grapheme_break = 0;
	if (cbc == 0 && prev_cbc != 0 && prev_cbc != 1 && prev_cbc != 2 && prev_cbc != 3)
		grapheme_break = 0;
	if (cbc == 1 && prev_cbc != 0 && prev_cbc != 1 && prev_cbc != 2 && prev_cbc != 3)
		grapheme_break = 0;
	if (cbc == 2 && prev_cbc != 0 && prev_cbc != 1 && prev_cbc != 2 && prev_cbc != 3)
		grapheme_break = 0;
	if (cbc == 3 && prev_cbc != 0 &&