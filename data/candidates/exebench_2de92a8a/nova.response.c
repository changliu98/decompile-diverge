static int sprint_int_number_nonlocalized(char *buf, int num, int precision, int is_negative)
{
	int count = 0, i, j;
	int is_zero = 0;
	int is_one_before_max = 0;
	int divisor = 1000000000;

	if (precision < 1)
		precision = 0;
	if (precision > 9)
		is_one_before_max = 1;
	if (num < 1) {
		is_zero = 1;
		num = -num;
	}
	while (1) {
		i = num / divisor;
		num = num % divisor;
		if (i || is_zero || count) {
			buf[count++] = i + '0';
			is_zero = 1;
		}
		divisor = divisor / 10;
		j = divisor;
		if (j == 1)
			break;
		if (precision == j)
			is_one_before_max = 1;
	}
	if (!is_negative &&!is_one_before_max)
		buf[count++] = '0';
	buf[count] = 0;
	return count;
}