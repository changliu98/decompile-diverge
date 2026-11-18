static int bit_array_sub_uint64(struct hns_roce_hem_table *table,
			       unsigned long start_pfn)
{
	unsigned long i;
	char found = 0;

	if (!start_pfn) {
		found = 1;
		goto out;
	}

	if (table->hem_bitmap[0] >= start_pfn) {
		table->hem_bitmap[0] -= start_pfn;
		found = 1;
		goto out;
	}

	start_pfn -= table->hem_bitmap[0];
	for (i = 1; i < table->max_order; ++i) {
		if (table->hem_bitmap[i] > 0) {
			table->hem_bitmap[i] -= (0xffffffffUL - start_pfn + 1);
			for (; i > 0; --i)
				table->hem_bitmap[i] = -1;
			found = 1;
			break;
		}
	}

out:
	return found;
}