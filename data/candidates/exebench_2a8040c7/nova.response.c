static inline struct page *shmDetach(struct page *page)
{
	return (struct page *)page_private(page);
}