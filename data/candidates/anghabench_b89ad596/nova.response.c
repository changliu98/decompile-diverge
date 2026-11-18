static inline size_t xfs_cui_log_format_sizeof(unsigned int nr_entries)
{
	return sizeof(struct iova_magazine) +
		nr_entries * sizeof(struct iova_magazine_entry);
}