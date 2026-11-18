static int sortedarray_insert(struct btree_geo *geo, unsigned long *node)
{
	int ret, i, j, k, n;
	unsigned long *new;

	if (!geo) {
		ret = 0;
		goto out;
	}

	n = geo->no_pairs;
	i = 0;
	while (1) {
		j = n;
		k = n;
		if (j > 1)
			k = (n + j) >> 1;
		if (i == k)
			break;
		j = k;
		n = j;
		ret = cmp_node(node, geo->node[i], k);
		if (ret < 0) {
			n = k;
		} else if (ret > 0) {
			i = k + 1;
		} else {
			break;
		}
	}

	if (geo->no_pairs + 1 > geo->max_pairs) {
		n = geo->max_pairs * 2;
		new = kmalloc_array(n, sizeof(unsigned long), GFP_KERNEL);
		if (!new) {
			ret = 0;
			goto out;
		}
		geo->node = new;
		geo->max_pairs = n;
	}

	memmove(&geo->node[i + 1], &geo->node[i],
		(geo->no_pairs - i) * sizeof(unsigned long));
	geo->node[i] = node;
	geo->no_pairs++;
	ret = 1;
out:
	return ret;
}