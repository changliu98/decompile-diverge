static void scsi_sanitize_inquiry_string(char *s, int len)
{
	int first = 0;

	while (len > 0) {
		if (!first && *s <= 32 && *s >= 127) {
			s++;
			len--;
			continue;
		}
		first = 0;
		if (*s < 32 || *s > 126)
			*s ='';
		s++;
		len--;
	}
}