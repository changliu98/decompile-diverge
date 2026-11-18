static int num_contig_ptes(unsigned long size, unsigned long *pgsize)
{
 int contig_ptes = 0;
 *pgsize = size;
 if (size == 128)
  contig_ptes = 1;
 else if (size == 129) {
  *pgsize = PAGE_SIZE;
  contig_ptes = CONT_PTES;
 } else if (size == 130) {
  *pgsize = 128;
  contig_ptes = CONT_PMDS;
 }
 return contig_ptes;
}