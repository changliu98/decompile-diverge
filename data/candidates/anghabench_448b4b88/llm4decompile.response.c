bool s390_cpumsf_reached_trailer(size_t entry_sz, size_t pos)
{
	size_t payload;

	payload = S390_CPUMSF_PAGESZ - (pos & (S390_CPUMSF_PAGESZ - 1));
	return entry_sz <= payload - sizeof(struct s390_cpumsf_trailer);
}