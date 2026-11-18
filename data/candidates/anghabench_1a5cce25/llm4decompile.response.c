int num_contig_ptes(unsigned long size, size_t *pgsize)
{
	int contig_ptes = 0;

	*pgsize = size;
	switch (size) {
	case PGSIZE_4K:
		contig_ptes = CONT_PMDS;
		*pgsize = PGSIZE_2M;
		break;
	case PGSIZE_2M:
		contig_ptes = CONT_PTES;
		*pgsize = PAGE_SIZE;
		break;
	case PAGE_SIZE:
		contig_ptes = 1;
		break;
	}
	return contig_ptes;
}