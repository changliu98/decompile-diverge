static struct page **func0(unsigned long order)
{
	struct page **pages;

	pages = (struct page **)malloc(sizeof(struct page *) * (1UL << order));
	if (!pages)
		return NULL;

	pages[0] = alloc_pages(GFP_KERNEL, order);
	if (!pages[0]) {
		free(pages);
		return NULL;
	}

	memset(pages, 0, sizeof(struct page *) * (1UL << order));
	pages[1] = pages[0] + (1UL << (order - 1));
	pages[2] = pages[0] + (2UL << (order - 1));

	return pages;
}