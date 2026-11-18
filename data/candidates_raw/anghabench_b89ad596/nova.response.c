static inline size_t func0(unsigned int nr_entries)
{
	return sizeof(struct iova_magazine) +
		nr_entries * sizeof(struct iova_magazine_entry);
}