static int try_enlarge(struct jffs2_sb_info *c, uint32_t nodesize)
{
	uint32_t old_size = c->flash_size;
	uint32_t new_size = old_size;
	void *new_node;
	int ret;

	while (1) {
		if (new_size < (c->sector_size + nodesize)) {
			new_size <<= 1;
			continue;
		}
		
		break;
	}

	new_node = kmalloc(new_size, GFP_KERNEL);
	if (!new_node) {
		ret = -1;
		goto err;
	}

	c->mtd = mtd_concat_add(c->mtd, new_size);
	c->flash_size = new_size;

	ret = 0;
err:
	return ret;
}