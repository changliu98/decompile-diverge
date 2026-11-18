static int mobi_decompress_huffman_internal(struct hashfile *f,
				struct pack_idx_entry *base_entry,
				struct pack_idx_entry *entry,
				uint32_t base_offset)
{
	uint32_t offset, base_offset_mask, base_offset_bits;
	uint32_t base_offset_shift;
	uint32_t base_idx, idx;
	uint32_t base_hash, hash;
	uint32_t base_size, size;
	uint32_t base_flags, flags;
	uint32_t base_mtime, mtime;
	uint32_t base_dev, dev;
	uint32_t base_ino, ino;
	uint32_t base_mode, mode;

	if (base_offset > 0x14)
		base_offset_shift = 3;
	else
		base_offset_shift = 0;

	base_offset_mask = (1 << base_offset_shift) - 1;
	base_offset_bits = base_offset >> base_offset_shift;

	do {
		base_idx = base_entry->nr;
		base_hash = base_entry->hash;
		base_size = base_entry->size;
		base_flags = base_entry->flags;
		base_mtime = base_entry->mtime;
		base_dev = base_entry->dev;
		base_ino = base_entry->ino;
		base_mode = base_entry->mode;

		idx = entry->nr;
		hash = entry->hash;
		size = entry->size;
		flags = entry->flags;
		mtime = entry->mtime;
		dev = entry->dev;
		ino = entry->ino;
		mode = entry->mode;

		offset = base_offset - (base_offset & base_offset_mask);
		base_offset -= base_offset_mask + 1;

		if (