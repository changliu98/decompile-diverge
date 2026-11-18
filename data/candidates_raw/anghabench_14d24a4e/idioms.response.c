int get_block_id(int page_id)
{
  int block_id = (page_id - 1) / 2;
  int page_in_block = (page_id - 1) % 2;
  int page_offset = (page_in_block * 3 + 1);
  int block_offset = (page_in_block * 2 + 2);
  return (block_id + page_offset + block_offset);
}