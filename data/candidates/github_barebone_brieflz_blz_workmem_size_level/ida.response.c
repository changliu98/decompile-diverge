size_t __cdecl blz_workmem_size_level(size_t src_size, int level)
{
  size_t v3; // [rsp+18h] [rbp-8h]

  switch ( level )
  {
    case 1:
      v3 = blz_workmem_size(src_size);
      break;
    case 2:
      v3 = blz_lazy_workmem_size(src_size);
      break;
    case 3:
      v3 = blz_hashbucket_workmem_size(src_size, 2u);
      break;
    case 4:
      v3 = blz_hashbucket_workmem_size(src_size, 4u);
      break;
    case 5:
    case 6:
    case 7:
      v3 = blz_leparse_workmem_size(src_size);
      break;
    case 8:
    case 9:
    case 10:
      v3 = blz_btparse_workmem_size(src_size);
      break;
    default:
      v3 = -1LL;
      break;
  }
  return v3;
}