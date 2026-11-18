size_t xfs_cui_log_format_sizeof(uint num_items)
{
	return (ulong)num_items * 4 + 4;
}