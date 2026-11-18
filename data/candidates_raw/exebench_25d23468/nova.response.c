static inline void func0(struct buffer_head *bh, int offset)
{
	if (offset >= 64) {
		bh->b_data = (char *)(bh->b_data + 64);
		bh->b_bdev = NULL;
	}
	bh->b_data = (char *)((unsigned long)bh->b_data & ~63);
	bh->b_data[0] = bh->b_data[0] | ((offset & 63) << (8 * sizeof(void *)));
	bh->b_bdev = (struct block_device *)((unsigned long)bh->b_data[0] >> 63);
	bh->b_data = (char *)((unsigned long)bh->b_data & ~(64 * sizeof(void *)));
}