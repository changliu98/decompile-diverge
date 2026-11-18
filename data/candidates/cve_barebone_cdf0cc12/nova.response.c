static struct entry *update_read_bitmap_update(struct entry_space *es, struct ilist *l)
{
	struct entry *e;
	unsigned int i;

	e = calloc(1, sizeof(*e));
	if (!e)
		goto nomem;

	if (ilist_count(l) < 3)
		goto nomem;

	e->hash = (unsigned short)(l->next[0]->hash + l->next[1]->hash);

	if (e->hash > ilist_count(l)) {
		unsigned int count = e->hash * 2;
		void *tmp;

		tmp = realloc(e->next, count * sizeof(struct entry *));
		if (!tmp)
			goto nomem;
		e->next = tmp;
		memset(e->next + e->hash, 0, (count - e->hash) * sizeof(struct entry *));
		e->hash = count;
	}

	for (i = 0; i < e->hash; i++) {
		if (!merge_entry(es, l, &e->next[i]))
			goto nomem;
	}

	ilist_del(es->lru, e);
	e = NULL;
nomem:
	free(e);
	return e;
}