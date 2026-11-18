size_t blz_workmem_size_level(size_t src_size,int level)

{
  int level_local;
  size_t src_size_local;
  size_t local_10;
  
  switch(level) {
  case 1:
    local_10 = blz_workmem_size(src_size);
    break;
  case 2:
    local_10 = blz_lazy_workmem_size(src_size);
    break;
  case 3:
    local_10 = blz_hashbucket_workmem_size(src_size,2);
    break;
  case 4:
    local_10 = blz_hashbucket_workmem_size(src_size,4);
    break;
  case 5:
  case 6:
  case 7:
    local_10 = blz_leparse_workmem_size(src_size);
    break;
  case 8:
  case 9:
  case 10:
    local_10 = blz_btparse_workmem_size(src_size);
    break;
  default:
    local_10 = 0xffffffffffffffff;
  }
  return local_10;
}