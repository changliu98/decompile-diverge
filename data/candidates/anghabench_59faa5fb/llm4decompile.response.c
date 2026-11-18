void scsi_sanitize_inquiry_string(unsigned char *s, int len)
{
	int terminated = 0;

	while (len-- > 0) {
		if (*s == 0)
			terminated = 1;
		if (terminated || *s < 0x20 || *s > 0x7e)
			*s = ' ';
		s++;
	}
}