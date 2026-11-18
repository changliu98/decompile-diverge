ssize_t
archive_string_append_from_wcs(archive_string *as, const wchar_t *wcs, size_t len)
{
	char *p, *end;
	int mb_len;
	ssize_t ret_val = 0;
	mbstate_t shift_state;

	memset(&shift_state, 0, sizeof(shift_state));

	if (archive_string_ensure(as, as->length + len + 1) == NULL)
		return (-1);

	p = as->s + as->length;
	end = as->s + as->buffer_length - __ctype_get_mb_cur_max() - 1;

	while (*wcs != L'\0' && len > 0) {
		if (p >= end) {
			as->length = p - as->s;
			as->s[as->length] = '\0';
			if (archive_string_ensure(as, as->length + len * 2 + 1)
			    == NULL)
				return (-1);
			p = as->s + as->length;
			end = as->s + as->buffer_length - __ctype_get_mb_cur_max() - 1;
		}
		mb_len = wcrtomb(p, *wcs, &shift_state);
		if (mb_len == -1) {
			if (*__errno_location() == 84) {
				*p = '?';
				p++;
			} else {
				ret_val = -1;
				break;
			}
		} else
			p += mb_len;
		wcs++;
		len--;
	}
	as->length = p - as->s;
	as->s[as->length] = '\0';
	return (ret_val);
}