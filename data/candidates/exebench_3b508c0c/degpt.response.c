size_t bnode_link_set_ref(size_t *link_ptr, size_t node_index)
{
  // Set the reference bit (bit 0) and store the index shifted left by 1.
  // The index is incremented by 1 before shifting to reserve 0 as a null value.
  size_t new_link_value = *link_ptr & 1 | (node_index + 1) * 2;
  *link_ptr = new_link_value;
  return new_link_value;
}