static struct mbuf *
conv_content_model(struct mbuf *m, struct tcphdr *th)
{
	struct mbuf *n;
	uint8_t *data;
	int i;

	n = NULL;
	if ((data = m_getdata(m->m_next))!= NULL) {
		KASSERT(m->m_next->m_len < (1 << 31),
		    ("conv_content_model: m_next->m_len too large"));
		for (i = 0; i < m->m_next->m_len; i++) {
			if ((data = tcp_scan(m->m_data + i, th, data)) == NULL) {
				m_freem(data);
				n = NULL;
				break;
			}
			n = m_getcl(data, i, data, m->m_len, m->m_type, n);
		}
		n = m_getcl(m->m_data, m->m_len, m->m_data, m->m_len,
		    m->m_type, n);
	}
	return (n);
}