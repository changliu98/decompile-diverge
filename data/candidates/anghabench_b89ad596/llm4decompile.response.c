size_t
xfs_cui_log_format_sizeof(unsigned int nr)
{
	return sizeof(struct xfs_cui_log_format) +
	       nr * sizeof(struct xfs_cui_log_format_entry);
}