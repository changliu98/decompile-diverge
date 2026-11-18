static int resize_vbar_entry(struct iommu_table *tbl, struct iommu_pool *pool)
{
	unsigned int npages;
	unsigned int pool_size;
	unsigned int pool_start;
	unsigned int pool_end;
	unsigned int pool_page;
	unsigned int *p;
	int ret;

	if (pool->npages > pool->nr_pages_limit) {
		npages = get_order(tbl->it_size);
		pool_size = pool->nr_pages_limit * npages;
		pool_start = pool->nr_pages_limit * (npages - pool->npages);
		pool_end = pool->nr_pages_limit;
	} else {
		npages = get_order(tbl->it_size);
		pool_size = pool->npages * npages;
		pool_start = 0;
		pool_end = pool->npages;
	}

	pool_page = pool_start * npages;
	p = kcalloc(pool_size, sizeof(unsigned int), GFP_KERNEL);
	if (!p) {
		ret = 0;
	} else {
		memset(p + pool_page, 0, (pool_end - pool_start) * npages);
		pool->pages = p;
		if (!pool->pages || pool->npages == 0)
			ret = 0;
		else
			ret = 1;
	}

	return ret;
}