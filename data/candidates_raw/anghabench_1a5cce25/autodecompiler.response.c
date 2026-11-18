__attribute__((used)) static int base_to_contig(unsigned long base, unsigned long *pgsz)
{
	unsigned long pgmask;
	int ret = 0;

	*pgsz = base;
	pgmask = base - 1UL;

	switch (pgmask) {
	case (128UL * 1024UL) - 1UL:
		ret = 1;
		break;
	case (128UL * 1024UL * 1024UL) - 1UL:
		*pgsz = (128UL * 1024UL);
		ret = CONT_PMDS;
		break;
	case (128UL * 1024UL * 1024UL * 1024UL) - 1UL:
		*pgsz = PAGE_SIZE;
		ret = CONT_PTES;
	}

	return ret;
}