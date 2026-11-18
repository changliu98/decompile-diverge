static const char *
convert_set_base(const char *strp, int *basep)
{

	*basep = 10;
	if (strp && *strp == '0') {
		switch (*++strp) {
		case 'x':
		case 'X':
			*basep = 16;
			
		case 'd':
		case 'D':
		case 'o':
		case 'O':
		case 'b':
		case 'B':
			strp++;
			break;
		default:
			strp = NULL;
		}
	}
	return (strp);
}