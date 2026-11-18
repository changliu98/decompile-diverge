size_t blz_workmem_size_level(unsigned level, unsigned type) {
  size_t size;
  switch (type) {
    case 1:
      size = blz_workmem_size(level);
      break;
    case 2:
      size = blz_lazy_workmem_size(level);
      break;
    case 3:
      size = blz_hashbucket_workmem_size(level, 2);
      break;
    case 4:
      size = blz_hashbucket_workmem_size(level, 4);
      break;
    case 5:
    case 6:
    case 7:
      size = blz_leparse_workmem_size(level);
      break;
    case 8:
    case 9:
    case 10:
      size = blz_btparse_workmem_size(level);
      break;
    default:
      size = (size_t)-1;
      break;
  }
  return size;
}