size_t blz_workmem_size_level(size_t src_size, int level) {
 size_t workmem_size;

 switch (level) {
 case 1:
  workmem_size = blz_workmem_size(src_size);
  break;
 case 2:
  workmem_size = blz_lazy_workmem_size(src_size);
  break;
 case 3:
  workmem_size = blz_hashbucket_workmem_size(src_size, 2);
  break;
 case 4:
  workmem_size = blz_hashbucket_workmem_size(src_size, 4);
  break;
 case 5:
 case 6:
 case 7:
  workmem_size = blz_leparse_workmem_size(src_size);
  break;
 case 8:
 case 9:
 case 10:
  workmem_size = blz_btparse_workmem_size(src_size);
  break;
 default:
  workmem_size = (size_t)-1;
 }

 return workmem_size;
}