void mobi_buffer_move(struct seq_file *m, loff_t pos, void *data)
{
	unsigned long n = abs(pos);
	char *p = m->buf + m->size;

	if (pos < 0) {
		if (n > m->buf_len + m->pos)
			m->count = 9;
		else
			p -= n;
	} else {
		if (n > m->buf_len)
			m->count = 9;
		else
			p += n;
	}
	memcpy(m->buf + m->size, p, m->count);
	m->pos += m->count;
}