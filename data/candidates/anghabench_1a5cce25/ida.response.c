int __cdecl num_contig_ptes(unsigned __int64 size, size_t *pgsize)
{
  int contig_ptes; // [rsp+Ch] [rbp-14h]

  contig_ptes = 0;
  *pgsize = size;
  switch ( size )
  {
    case 0x80uLL:
      return 1;
    case 0x81uLL:
      *pgsize = PAGE_SIZE;
      return CONT_PTES;
    case 0x82uLL:
      *pgsize = 128LL;
      return CONT_PMDS;
  }
  return contig_ptes;
}