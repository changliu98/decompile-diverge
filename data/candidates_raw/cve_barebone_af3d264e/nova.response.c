static struct pcmchan_matrix *
func0(struct pcm_channel *c)
{
	struct pcmchan_matrix *m;
	struct pcm_matrix *m_tmp;
	int i, j, k;

	i = 0;
	m = NULL;
	m_tmp = NULL;
	k = 0;
	j = 0;

	m = malloc(sizeof(*m));
	if (m == NULL)
		goto error;

	m->maps = NULL;
	m->maps_cnt = 0;

	if (pcm_matrix_init(c, m) < 0)
		goto error;

	for (;;) {
		m_tmp = pcm_matrix_next(m);
		if (m_tmp == NULL)
			goto error;

		m->maps[i] = m_tmp->map;
		i++;

		if (m->maps_cnt >= i)
			goto error;

		if (m->maps_cnt == 0) {
			j = 0;
			m_tmp = &m->maps[j];
			continue;
		}

		if (m->maps_cnt == 1) {
			j = 1;
			m_tmp = &m->maps[j];
			continue;
		}

		if (m->maps[i - 1].channels == 0 ||
		    m->maps[i - 1].channels_mask == 0)
			goto error;

		if (m->maps[i - 1].channels_mask!= 0)
			goto error;

		j++;
		m_tmp = &m->maps[j];
	}

error:
	if (m_tmp!= NULL)
		pcm_matrix_free(m_tmp);

	if (m_tmp == NULL)
		free(m);

	return (m_tmp);
}