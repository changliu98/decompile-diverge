static int itoa(char *str, int num)
{
	int i, j, pos, neg, res, temp, size;

	if (num == 0) {
		str[0] = '0';
		str[1] = '\0';
		res = 2;
	} else {
		res = 0;
		neg = 1;
		if (num < 0) {
			temp = -num;
		} else {
			temp = num;
		}
		while (temp) {
			j = temp % 10;
			temp = temp / 10;
			if (temp!= 0) {
				res++;
			}
		}
		if (num < 0) {
			res++;
			neg = 0;
		}
		size = res;
		pos = res - 1;
		while (pos >= 0) {
			i = num / neg;
			str[pos] = (i % 10) + '0';
			neg = neg * 10;
			pos--;
		}
		if (num < 0) {
			str[0] = '-';
		}
		str[size] = '\0';
		res = size;
	}
	return res;
}