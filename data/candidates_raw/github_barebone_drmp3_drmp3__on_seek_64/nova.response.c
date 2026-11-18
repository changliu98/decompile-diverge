static int func0(FILE *fp, unsigned long off, int iTmp)
{
	int i;

	if (off <= 0x7FFFFFFFUL) {
		i = fseek(fp, off, SEEK_SET);
	} else {
		if (!fseek(fp, 0x7FFFFFFF, SEEK_SET))
			i = 0;
		else
			return 0;

		while (off > 0x7FFFFFFFUL) {
			if (off > 0xFFFFFFFFUL - 0x7FFFFFFFUL) {
				if (!fseek(fp, 0x7FFFFFFF, SEEK_CUR))
					i = 0;
				else
					return 0;
			} else {
				off -= 0x7FFFFFFFUL;
				if (!fseek(fp, (long)off, SEEK_CUR))
					i = 0;
				else
					return 0;
			}
		}
	}

	return i;
}