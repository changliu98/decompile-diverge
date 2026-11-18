bool issymbol(char c) {
	switch (c) {
	case '+':
	case '-':
	/* case '/': not good for dalvik */
	case '>':
	case '<':
	case '(':
	case ')':
	case '*':
	case '%':
	case ']':
	case '[':
	case ',':
	case ' ':
	case '{':
	case '}':
		return true;
	default:
		return false;
	}
}