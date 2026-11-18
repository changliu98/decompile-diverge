static int get_name_len(int n, const unsigned char *buf, const unsigned char *end, const unsigned char *top, int *cnt, int *sz)
{
	int ret;
	unsigned short len;
	unsigned char *p;

	while (1) {
		while (buf < end && *buf < 0x80) {
			buf++;
			(*cnt)++;
		}
		if (buf >= end)
			return 0x00010003;
		if ((*buf & 0xc0)!= 0x80)
			break;
		(*cnt) = 0;
		(*sz) = 0;
		p = (unsigned char *)buf;
		while (p < end && (*p & 0xc0) == 0x80) {
			ret = get_name_len(n + 1, p, end, top, cnt, sz);
			if (ret)
				return ret;
			(*cnt)++;
			(*sz) += n + 1;
			ret = 0x0000;
			p += n + 1;
		}
		len = *p;
		if (buf + len > end)
			return 0x00010003;
		buf++;
		(*cnt)++;
		(*sz)++;
	}
	return 0;
}