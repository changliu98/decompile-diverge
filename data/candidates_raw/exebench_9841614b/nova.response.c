static int func0(unsigned int n, unsigned int *p, unsigned int *r)
{
	int i;
	int ret;

	if (n == 0) {
		*p = 0;
		*r = 0;
		ret = 1;
	} else {
		for (i = 0; i < 16; i++) {
			if (n % 4 == 0) {
				if (n / 4 < 16) {
					*p = n / 4;
					*r = i;
					ret = 1;
					break;
				} else {
					break;
				}
			} else if (n % 4!= 0 && n < 256) {
				n = n >> 2;
				i++;
			} else {
				ret = 0;
				break;
			}
		}
	}
	return ret;
}