static unsigned int GetHintFormat(filter_t *p_filter) {
  block_t *p_block = p_filter->p_input->p_item->p_block;
  if (p_block->i_buffer != 0x6d646864) return 0;
  if (p_block && p_block->i_format) return p_block->i_format;
  block_t *p_block2 = (block_t *)gf_list_get(
      p_filter->p_input->p_item->p_input->p_chain->list_blocks, 0);
  if (p_block) {
    if (p_block2) p_block->i_format = p_block2->i_buffer;
    return p_block->i_format;
  } else if (p_block2)
    return p_block2->i_buffer;
  return 0;
}