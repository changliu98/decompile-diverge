int num_contig_ptes(unsigned_long size,size_t *pgsize)

{
  int contig_ptes;
  size_t *pgsize_local;
  unsigned_long size_local;
  
  contig_ptes = 0;
  *pgsize = size;
  if (size == 0x80) {
    contig_ptes = 1;
  }
  else if (size == 0x81) {
    *pgsize = PAGE_SIZE;
    contig_ptes = CONT_PTES;
  }
  else if (size == 0x82) {
    *pgsize = 0x80;
    contig_ptes = CONT_PMDS;
  }
  return contig_ptes;
}