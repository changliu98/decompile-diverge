static char read_escape_control_char(char c)
{
	char ret;

	switch (c) {
	case 'n':
		ret = '\n';
		break;
	case 't':
		ret = '\t';
		break;
	case 'r':
		ret = '\r';
		break;
	case 'e':
		ret = '\e';
		break;
	case 'b':
		ret = '\b';
		break;
	case 'f':
		ret = '\f';
		break;
	case 'v':
		ret = '\v';
		break;
	default:
		ret = c;
		break;
	}
	return ret;
}