static int num_contig_ptes(unsigned long size, unsigned long *pte_size) {
  int nptes = 0;
  *pte_size = size;
  switch (size) {
    case PAGE_SIZE:
      nptes = 1;
      break;
    case PUD_SIZE:
      *pte_size = PTE_SIZE;
      nptes = PTRS_PER_PUD;
      break;
    case PMD_SIZE:
      *pte_size = 128;
      nptes = PTRS_PER_PMD;
      break;
  }
  return nptes;
}