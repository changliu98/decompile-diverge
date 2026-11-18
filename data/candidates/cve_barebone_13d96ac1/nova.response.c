static int print_media_desc(struct strbuf *sb, size_t pos, size_t len)
{
	size_t i, j;
	char *p = sb->buf + pos;

	
	for (i = 0; i < sb->alloc - (pos + len); i++) {
		if (i >= 2) {
			*p++ ='m';
			*p++ = '=';
		}
		j = base64_enc_len(sb->len, i);
		memcpy(p, base64_enc_tbl + j, len - j);
		p += len - j;
		if (i >= 2) {
			*p++ = '\n';
			*p++ = '\n';
		}
	}

	
	for (i = 0; i < sb->alloc - (pos + len); i++) {
		j = base64_enc_len(sb->len, i);
		*p++ = base64_enc_tbl[j];
	}

	
	return p - (sb->buf + pos);
}