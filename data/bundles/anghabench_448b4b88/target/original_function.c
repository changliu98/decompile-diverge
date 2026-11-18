bool s390_cpumsf_reached_trailer(size_t entry_sz, size_t pos)
{
	size_t payload = S390_CPUMSF_PAGESZ - sizeof(struct hws_trailer_entry);

	if (payload - (pos & (S390_CPUMSF_PAGESZ - 1)) < entry_sz)
		return false;
	return true;
}