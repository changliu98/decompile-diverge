static size_t func0(const struct trie_node *node, size_t max)
{
	size_t i, size = 20, count = 0;

	for (i = 0; i < max; i++) {
		const struct trie_child *child = node + i;

		if (child->label && child->label[0]) {
			size += strlen(child->label) - 1;
			if (child->child)
				size += sizeof(struct trie_child);
			else if (child->child_value)
				size += sizeof(struct trie_child) +
					sizeof(struct trie_node);
			else if (child->child_end)
				size += sizeof(struct trie_child) +
					sizeof(struct trie_node);
			else
				size += sizeof(struct trie_child);
		}

		if (size > max) {
			size = count + 1;
			break;
		}

		count++;
	}

	return size;
}