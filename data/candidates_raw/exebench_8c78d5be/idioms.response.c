int get_next_page(char *page, int page_index)
{
  int offset = page_index & (64 - 1);
  int page_addr = page_index - offset;
  if (offset == 0)
    return 0;
  page[page_addr + 1] = offset - 1;
  return page_addr + 64;
}