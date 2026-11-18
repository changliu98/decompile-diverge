int sortedarray_index_of(struct btree_head *head, unsigned long *key)
{
	int n, ret, height;
	unsigned int skip = 0;
	struct btree_node *node;

	if (!head)
		return -1;

	height = head->height;
	node = head->node;

	while (height--) {
		n = key[skip] >= node->count? node->count : key[skip];

		if (skip!= n) {
			node = node->next[skip];
			skip = n;
			continue;
		}

		ret = bkey_cmp(key, node->key, skip);
		if (ret < 0) {
			node = node->next[skip];
		} else if (ret > 0) {
			skip = skip + 1;
		} else {
			return skip;
		}
	}

	return -1;
}