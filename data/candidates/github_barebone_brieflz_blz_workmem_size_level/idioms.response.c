unsigned long blz_workmem_size_level(unsigned long src_size, int level)
{
  unsigned long block_size = -1;
  switch (level) {
  case 1:
    block_size = get_block_size_for_level1(src_size);
    break;
  case 2:
    block_size = get_block_size_for_level2(src_size);
    break;
  case 3:
    block_size = get_block_size_for_level3(src_size, 2);
    break;
  case 4:
    block_size = get_block_size_for_level3(src_size, 4);
    break;
  case 5:
  case 6:
  case 7:
    block_size = get_block_size_for_level4(src_size);
    break;
  case 8:
  case 9:
  case 10:
    block_size = get_block_size_for_level5(src_size);
    break;
  default:
    block_size = -1;
  }
  return block_size;
}