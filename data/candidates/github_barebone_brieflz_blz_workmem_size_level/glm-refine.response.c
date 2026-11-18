size_t __cdecl blz_workmem_size_level(size_t src_size, int level)
{
  switch (level)
  {
    case 1:
      return blz_workmem_size(src_size);
    case 2:
      return blz_lazy_workmem_size(src_size);
    case 3:
      return blz_hashbucket_workmem_size(src_size, 2u);
    case 4:
      return blz_hashbucket_workmem_size(src_size, 4u);
    case 5:
    case 6:
    case 7:
      return blz_leparse_workmem_size(src_size);
    case 8:
    case 9:
    case 10:
      return blz_btparse_workmem_size(src_size);
    default:
      return (size_t)-1;
  }
}