static const char *check_longlong_async_signal_safe(const char *str, int *l_case)
{
	*l_case = 0;
	if (*str == 'l') {
		str++;
		if (*str!= 'l')
			*l_case = 1;
		else
			str++;
		*l_case = 1;
	}
	return str;
}