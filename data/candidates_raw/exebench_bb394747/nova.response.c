static int func0(struct btree_node *n)
{
	int count = 1;

	while (count < n->header.max_entries &&
	       node_entry_is_pointer(n, count))
		count = count << 1;

	n->header.max_entries = count;

	return count - 1;
}