static int jpegxl_anim_read_packet(struct dm_target *ti, struct bio *bio)
{
	struct dm_verity *v = ti->private;
	struct dm_verity_io *io = ti->private;
	size_t len;
	int r;
	sector_t block_nr;

	block_nr = dm_target_offset(ti, bio->bi_iter.bi_sector);
	if (block_nr < 0) {
		r = block_nr;
		goto fail;
	}

	if (block_nr == 0)
		block_nr = 4096;

	if (v->data_start && block_nr < v->data_start->start)
		block_nr = v->data_start->start;

	r = verity_hash(io, block_nr);
	if (r < 0)
		goto fail;

	if (v->data_start) {
		len = v->data_start->start;
		memcpy(bio->bi_iter.bi_sector, v->data_start->digest, len);
		verity_hash_update(v);
	}

	r = verity_hash_final(io, bio->bi_iter.bi_sector + len,
			      block_nr - len);
	if (r < 0)
		goto fail;

	if (r < block_nr - len)
		bio->bi_iter.bi_size = r + len;

	r = 0;
fail:
	return r;
}