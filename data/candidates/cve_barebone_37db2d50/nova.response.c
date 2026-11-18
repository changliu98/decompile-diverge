static int mobi_decompress_huffman_internal(struct msdos_sb_info *sbi,
			     struct msdos_dir_entry *de,
			     struct fat_slot_info *s, u32 start)
{
	unsigned int i, j, k, l, n, m, o, p;
	unsigned int mask, shift, offset;
	unsigned int len;
	unsigned int c;
	unsigned int ret;

	
	i = start;
	while (i < 20) {
		j = i;
		k = i;
		l = i;
		n = i;
		o = i;
		p = i;
		i = i + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1;
		n = n + 1;
		o = o + 1;
		p = p + 1;
		j = j + 1;
		k = k + 1;
		l = l + 1